#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
void Imprimir_No(T_No *no){
	printf("\t-> %c | %d | %d <-\n", no -> dados -> letra, no -> dados -> frequencia, no -> dados -> tamanho);
}

void Imprimir_Pre_Ordem(T_No *no){
	Imprimir_No(no);
	if(no -> direita != NULL){
		Imprimir_Pre_Ordem(no -> esquerda);
	}
	if(no -> direita != NULL){
		Imprimir_Pre_Ordem(no -> direita);
	}
}

void Monta_codigo(T_No *no, int vet[], int n, FILE *fd){
    if(no -> esquerda != NULL){
        vet[n] = 1;
		Monta_codigo(no -> esquerda, vet, n+1, fd);
	}
	if(no -> direita != NULL){
        vet[n] = 0;
		Monta_codigo(no -> direita, vet, n+1, fd);
	}
    if(no -> esquerda == NULL && no -> direita == NULL){
        int i;
        fprintf(fd,"%c: ", no -> dados -> letra);
        for(i = 0; i < n; i++){
            fprintf(fd, "%d", vet[i]);
        }
        fprintf(fd,"\n");
    }

}


int Lista_vazia(T_Lista *lista){
    if((lista -> primeiro == NULL) || (lista -> ultimo == NULL)){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
T_Lista *Aloca_lista(){
    T_Lista *ptr = (T_Lista *)malloc(sizeof(T_Lista));
    if(ptr == NULL){
        printf("Erro ao alocar a lista\n");      
    }
    else{
        ptr -> primeiro = NULL;
        ptr -> ultimo = NULL;
        ptr -> quantidade = 0;
    }
    return ptr;
}
T_Elemento *Aloca_elemento(T_Lista *lista){
    T_Elemento *ptr = (T_Elemento *)malloc(sizeof(T_Elemento));
    if(ptr == NULL){
        printf("Erro ao alocar elemento\n");
        return NULL;
    }
    else{
        ptr -> no = Aloca_no();
        if(ptr -> no == NULL){
            free(ptr);
            return NULL;
        }
        else{
            if(Lista_vazia(lista) == TRUE){
                lista -> primeiro = ptr;
                lista -> ultimo = ptr;
                lista -> quantidade++;
                ptr -> anterior = NULL;
                ptr -> proximo = NULL;
            }
            else{
                lista -> ultimo -> proximo = ptr;
                ptr -> anterior = lista -> ultimo;
                lista -> ultimo = ptr;
                lista -> quantidade++;
                ptr -> proximo = NULL;
            }
        }
    }
}
void Ordena_lista(T_Lista *lista){
    int i,trocou = TRUE;
    T_Dados aux;
    T_Elemento *atual = lista -> primeiro;
    T_Elemento *proximo = atual -> proximo;

    while(trocou == TRUE){
        trocou = 0;
        atual = lista -> primeiro;
        proximo = atual -> proximo;
        for(i = 0; i < lista -> quantidade -1; i++){
            if(atual -> no -> dados -> frequencia > proximo -> no -> dados -> frequencia){
                aux.frequencia = atual -> no -> dados -> frequencia;
                aux.letra = atual -> no -> dados -> letra;
                aux.tamanho = atual -> no -> dados -> tamanho;

                atual -> no -> dados -> frequencia = proximo -> no -> dados -> frequencia;
                atual -> no -> dados -> letra = proximo -> no -> dados -> letra;
                atual -> no -> dados -> tamanho = proximo -> no -> dados -> tamanho;

                proximo -> no -> dados -> frequencia = aux.frequencia;
                proximo -> no -> dados -> letra = aux.letra;
                proximo -> no -> dados -> tamanho = aux.tamanho;

                trocou = 1;
            }
            atual = atual -> proximo;
            proximo = proximo -> proximo;
        }
    }
     
}

T_No *Aloca_no(){
    T_No *ptr = (T_No*)malloc(sizeof(T_No));
    if(ptr == NULL){
        printf("Erro ao alocar No\n");
    }
    else{
        ptr -> dados = (T_Dados *)malloc(sizeof(T_Dados));
        if(ptr -> dados == NULL){
            printf("Erro ao alocar Dados do No\n");
            free(ptr);
            return NULL;
        }
        else{
            ptr -> esquerda = NULL;
            ptr -> direita = NULL;
            ptr -> dados -> tamanho = 0;
        }
    }
    return ptr;
}





void Verifica_ocorrencia(T_Ascii ascii[], char texto[], int n){     // funcao que verifica se tem ocorrencia de um caractere e quantas vezes ele ocorre
    int i;
    for(i = 0; i < n; i++){
        ascii[texto[i]].frequencia++;                          // para cada caractere encontrado, incrementar um na posicao referente a tabela ascii
        ascii[texto[i]].letra = texto[i];
    }
}
int Bubblesort(T_Ascii vet[], int fim){
    int i,j = 0,trocou = TRUE;
    T_Ascii aux;
    while(trocou == TRUE){
        trocou = 0;
        for(i = 0; i < fim -1 -j; i++){
            if(vet[i].frequencia > vet[i+1].frequencia){
                aux.frequencia = vet[i].frequencia;
                aux.letra = vet[i].letra;

                vet[i].frequencia = vet[i+1].frequencia;
                vet[i].letra = vet[i+1].letra;

                vet[i+1].frequencia = aux.frequencia;
                vet[i+1].letra = aux.letra;

                trocou = 1;
            }
        }
        j++;
    }     
}


void Le_arquivo(char vet[], int n, char arquivo[]){ // funcao que passa o que estah escrito no arquivo de texto para um vetor
    FILE *fd;                                       // descritor do arquivo
    int i;
    fd = fopen(arquivo, "r");                       // abrindo o arquivo para leitura
    for(i = 0; i < n ; i++){
        fscanf(fd,"%c", &vet[i]);                   // atribuindo cada um dos caracteres para uma posicao do vetor
    }
    fclose(fd);                                     // fechando o arquivo
}
int Verifica_tamanho_arquivo(char arquivo[]){       // funcao que abre o arquivo no final e verifica quantos bytes estao contidos nele
    FILE *fd;                                       // descritor do arquivo
    int tam;                                        // variavel pra guardar o tamanho do arquivo
    fd = fopen(arquivo, "a");                       // abrindo o arquivo com descritor apontando para o final dele
    tam = ftell(fd);                                // pega quantos bytes se passaram ate a posicao atual no arquivo
    fclose(fd);                                     // fecha o arquivo
    return tam;
}
void Remove_elemento (T_Lista *lista){
    T_Elemento *ptr = lista -> primeiro;            // salvando o ponteiro para a primeira posicao da lista em uma variavel auxiliar
    T_No *no = Aloca_no();                          // alocando espaço para o no que sera a soma das frequencias dos nos de menor frequencia
    T_No *primeiro = lista -> primeiro -> no;       // colocando o no de menor frequencia em uma variavel pra facilitar a visao
    T_No *segundo = lista -> primeiro -> proximo -> no;     // colocando o segundo no de menor frequencia em uma variavel pra facilitar a visao
    no -> dados -> frequencia =  (primeiro -> dados -> frequencia + segundo -> dados -> frequencia); // fazendo a frequencia do no criado ser igual a soma dos dois nos com menor frequencia
    no -> dados -> tamanho = (primeiro -> dados -> tamanho + segundo -> dados -> tamanho) + 1;
    no -> dados -> letra = '\0';   // colocando a letra desse no, por uma que nunca sera encontrada na string de texto
    no -> esquerda = primeiro;     // fazendo o no que foi criado apontar para o primeiro elemento da lista    
    no -> direita = segundo;       // fazendo o no que foi criado apontar para o segundo elemento da lista
    lista -> primeiro -> proximo -> no = no;    // fazendo o segundo elemento da lista apontar para o no que foi criado
    lista -> primeiro = lista -> primeiro -> proximo; // fazendo a lista apontar para o segundo elemento que agora e a fusao dos 2
    lista -> primeiro -> anterior = NULL;   // atualizando o ponteiro pro anterior ao primeiro da lista
    lista -> quantidade --;
    free(ptr);
}
T_No *Remove_ultimo_elemento (T_Lista *lista){
    T_Elemento *ptr = lista -> primeiro;
    T_No *no = ptr -> no;
    free(ptr);
    lista -> quantidade--;
    return no;
}
T_No *Cria_Huffman (T_Lista *lista){
    if(Lista_vazia(lista) == FALSE){
        while(lista -> quantidade > 1){
            Remove_elemento(lista);
            Ordena_lista(lista);
            Mostra_lista(lista);
            Imprimir_Pre_Ordem(lista -> primeiro -> no);
            printf("--------------------------\n");
        }
        return Remove_ultimo_elemento(lista);
    }
}
void Passo_a_passo(char arquivo[], char arquivo_tabela[]){                 // funcao responsavel por rodar o codigo
    int tam = Verifica_tamanho_arquivo(arquivo);
    char string[tam];                               // vetor para guardar o texto retirado do arquivo original
    int i, qtd_arvores;
    T_Lista *lista;
    T_No *huff;         // no onde ficara salvo a arvore de huffman
    lista = Aloca_lista();
    T_Ascii ascii[256];   // vetor para guarda em cada posicao se o caractere esta presente no vetor e quantas vezes aparece
    FILE *fd;
    for(i = 0; i < 256; i++){
        ascii[i].frequencia = 0;
        ascii[i].letra = i;
    }
    Le_arquivo(string, tam, arquivo);
    Verifica_ocorrencia(ascii, string, tam);
    Bubblesort(ascii, 256);
    for(i = 0; i < 256; i ++){
        printf("%d: %c %d\n", ascii[i].letra, ascii[i].letra, ascii[i].frequencia);
    }
    for(i = 0; i < 256; i++){
        if(ascii[i].frequencia != 0){
            Aloca_elemento(lista);
            lista -> ultimo -> no -> dados -> frequencia = ascii[i].frequencia;
            lista -> ultimo -> no -> dados -> tamanho = 1;
            lista -> ultimo -> no -> dados -> letra = ascii[i].letra;
        }
    }
    huff = Cria_Huffman(lista);
    free(lista);
    Imprimir_Pre_Ordem(huff);
    fd = fopen(arquivo_tabela, "w");
    int vet[huff -> dados -> tamanho];
    Monta_codigo(huff, vet, 0, fd);
    fclose(fd);
}
void Mostra_lista(T_Lista *lista){
    T_Elemento *ptr = lista -> primeiro;

    while(ptr != NULL){
        if(ptr -> no -> dados -> letra == '\0'){
            printf("> * ");
        } else{

            printf("> %c ", ptr -> no -> dados -> letra);
            if(ptr -> no -> esquerda != NULL){
                printf("ESQUERDA: %c ", ptr -> no -> esquerda -> dados -> letra);
            }
            if(ptr -> no -> direita != NULL){
                printf("DIREITA: %c \n", ptr -> no -> direita -> dados -> letra);
            }
        }
        ptr = ptr -> proximo;

    }
}