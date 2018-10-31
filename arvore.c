#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>


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
    int n = lista -> quantidade;
    int i, j;
    T_Elemento *ptr;
    for(i = 0; i < n; i++){
        ptr = lista -> primeiro;
        for(j = 0; j < n - i - 1; j++){
            if(ptr -> no -> dados -> frequencia > ptr -> proximo -> no -> dados -> frequencia){ // se frequencia do elemento atual for maior que a do proximo
                // Recomenda-se desenhar para entender essa parte
                ptr -> proximo -> anterior = ptr -> anterior;   // a traseira do proximo aponta para o ponteiro apontado pela traseira do atual
                ptr -> anterior = ptr -> proximo;               // a traseira do ponteiro atual aponta pro proximo
                ptr -> anterior -> proximo = ptr;               // a frente do ponteiro que era o proximo aponta pro ponteiro atual

                ptr -> proximo = ptr -> proximo -> proximo;     // a frente do ponteiro atual aponta pra frente do ponteiro que era o proximo (que no caso era o proximo do proximo)
                ptr -> proximo -> anterior = ptr;               // a traseira do proximo ao ponteiro atual aponta pro ponteiro atual
            }
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
int Quicksort(T_Ascii vet[], int inicio, int fim){
    int i = inicio, j = fim;
    int pivo = (inicio + fim) / 2;
    while(i < j){
        while(vet[pivo].frequencia > vet[i].frequencia)
            i++;
        while(vet[pivo].frequencia < vet[j].frequencia)
            j--;
        if(i<=j){
            T_Ascii aux;
            aux.frequencia = vet[i].frequencia;
            vet[i].frequencia = vet[j].frequencia;
            vet[j].frequencia = aux.frequencia;
            aux.letra = vet[i].letra;
            vet[i].letra = vet[j].letra;
            vet[j].letra = aux.letra;
            i++;
            j--;
        }
    }
    if(j>inicio)
        Quicksort(vet, inicio, j);
    if(i<fim)
        Quicksort(vet, i, fim);
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

    T_No *no = Aloca_no();
    T_No *primeiro = lista -> primeiro -> no;
    T_No *segundo = lista -> primeiro -> proximo -> no;
    no -> dados -> frequencia =  (primeiro -> dados -> frequencia + segundo -> dados -> frequencia);
    no -> dados -> tamanho = (primeiro -> dados -> tamanho + segundo -> dados -> tamanho) + 1;
    no -> dados -> letra = -1;
}

void Passo_a_passo(char arquivo[]){                 // funcao responsavel por rodar o codigo
    int tam = Verifica_tamanho_arquivo(arquivo);
    char string[tam];                               // vetor para guardar o texto retirado do arquivo original
    int i, qtd_arvores;
    T_Lista *lista;
    lista = Aloca_lista();
    T_Ascii ascii[256];   // vetor para guarda em cada posicao se o caractere esta presente no vetor e quantas vezes aparece
    for(i = 0; i < 256; i++){
        ascii[i].frequencia = 0;
        ascii[i].letra = i;
    }
    Le_arquivo(string, tam, arquivo);  
    Verifica_ocorrencia(ascii, string, tam);
    Quicksort(ascii, 0, 256);
    for(i = 0; i< 256; i++){
        printf("%d: %c %d\n", ascii[i].letra,ascii[i].letra,ascii[i].frequencia);
    }
    for(i = 0; i < 256; i++){
        if(ascii[i].frequencia != 0){
            Aloca_elemento(lista);
            lista -> ultimo -> no -> dados -> frequencia = ascii[i].frequencia;
            lista -> ultimo -> no -> dados -> tamanho = 1;
            lista -> ultimo -> no -> dados -> letra = ascii[i].letra;
        }
    }
}
