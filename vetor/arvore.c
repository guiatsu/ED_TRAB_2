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
void Passo_huff(T_No *vet[], int n){
    T_No *pai = Aloca_no();
    pai -> esquerda = vet[0];
    pai -> direita = vet[1];
    pai -> dados -> letra = '\0';
    pai -> dados -> frequencia = vet[0] -> dados -> frequencia + vet[1] -> dados -> frequencia;
    pai -> dados -> tamanho = vet[0] -> dados -> tamanho + vet[1] -> dados -> tamanho;;
    vet[0] = pai;
    int i;
    for(i = 1; i < n - 1; i ++){
        vet[i] = vet[i + 1];
    }
    vet[n - 1] = NULL;
}

void Ordena_lista(T_No *vet[], int n){
    int i,j = 0, trocou = TRUE;
    T_No *aux;
    while(trocou == TRUE){
        trocou = 0;
        for(i = 0; i < n -1 -j; i++){
            if(vet[i] -> dados -> frequencia > vet[i +1] -> dados -> frequencia){
                aux = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = aux;
                trocou = 1;
            }
            else{
                if(vet[i] -> dados -> frequencia == vet[i +1] -> dados -> frequencia){
                    if(vet[i] -> dados -> tamanho > vet[i +1] -> dados -> tamanho){
                        aux = vet[i];
                        vet[i] = vet[i + 1];
                        vet[i + 1] = aux;
                        trocou = 1;
                    }
                }
            }
        }
        j++;
    } 

}




T_No *Cria_Huffman(T_No *vet[], int n){
    while(n > 1){
        Mostra_vet(vet, n);
        Passo_huff(vet, n);
        n--;
        Ordena_lista(vet, n);
    }
    return vet[0];
}



void Passo_a_passo(char arquivo[], char arquivo_tabela[]){                 // funcao responsavel por rodar o codigo
    int tam = Verifica_tamanho_arquivo(arquivo);
    char string[tam];                               // vetor para guardar o texto retirado do arquivo original
    int i, j = 0, qtd_arvores = 0;
    T_No *huff;         // no onde ficara salvo a arvore de huffman
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
            qtd_arvores++;
        }
    }
    T_No *lista[qtd_arvores];
    for(i = 0; i < 256; i++){
        if(ascii[i].frequencia != 0){
            lista[j] = Aloca_no();
            lista[j] -> dados -> frequencia = ascii[i].frequencia;
            lista[j] -> dados -> letra = ascii[i].letra;
            lista[j] -> dados -> tamanho = 1;
            j++;
        }
    }
    huff = Cria_Huffman(lista, qtd_arvores);




    Imprimir_Pre_Ordem(huff);
    fd = fopen(arquivo_tabela, "w");
    int vet[huff -> dados -> tamanho];
    Monta_codigo(huff, vet, 0, fd);
    fclose(fd);
}
void Mostra_vet(T_No *vet[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%c | ", vet[i] -> dados -> letra);
        if(vet[i] -> dados -> letra != '\0'){
            if(vet[i] -> esquerda != NULL){
                printf("Esquerda: %c \t", vet[i] -> esquerda -> dados -> letra);
            }
            if(vet[i] -> direita != NULL){
                printf("Direita: %c\n", vet[i] -> direita -> dados -> letra);
            }
        }
    }
    printf("\n");
}