#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int Lista_vazia(T_Lista *lista){
    if(lista -> primeiro == NULL || lista -> ultimo == NULL){
        return TRUE;
    }
    return FALSE;
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
        printf("Erro ao alocar o elemento\n");
    }
    else{
        if(Lista_vazia(lista) == TRUE){
            lista -> primeiro = ptr;
            lista -> ultimo = ptr;
            lista -> quantidade++;
            ptr -> proximo = NULL;
            ptr -> anterior = NULL;
            ptr -> no = Aloca_no();
        }
        else{
            ptr -> anterior = lista -> ultimo;
            lista -> ultimo -> proximo = ptr;
            lista -> ultimo = ptr;
            lista -> quantidade++;
            ptr -> proximo = NULL;
            ptr -> no = Aloca_no();
        }
    }
}

void Ordena_lista(T_Lista *lista){
    T_Elemento *atual = lista -> primeiro;
    T_Elemento *proximo = atual -> proximo;
    int i,j = 0,trocou = TRUE;
    T_No *aux;
    while(trocou == TRUE){
        trocou = 0;
        atual = lista -> primeiro;
        proximo = atual -> proximo;
        for(i = 0; i < lista -> quantidade -1 -j; i++){
            if(atual -> no -> dados -> frequencia > proximo -> no -> dados -> frequencia){
                aux = atual -> no;
                atual -> no = proximo -> no;
                proximo -> no = aux;
                trocou = 1;

            }
            else{
                if(atual -> no -> dados -> tamanho > proximo -> no -> dados -> tamanho){
                    aux = atual -> no;
                    atual -> no = proximo -> no;
                    proximo -> no = aux;
                    trocou = 1;
                }
            }
            atual = atual -> proximo;
            proximo = proximo -> proximo;
        }
        j++;
    }  
}
void Remove_elemento(T_Lista *lista){
    T_Elemento *ptr = lista -> primeiro;
    T_No *pai = Aloca_no();
    pai -> esquerda = ptr -> no;
    pai -> direita = ptr -> proximo -> no;
    pai -> dados -> frequencia = (ptr -> no -> dados -> frequencia + ptr -> proximo -> no -> dados -> frequencia);
    pai -> dados -> tamanho = (ptr -> no -> dados -> tamanho + ptr -> proximo -> no -> dados -> tamanho) + 1;
    pai -> dados -> letra = '\0';
    ptr -> proximo -> no = pai;
    lista -> primeiro = lista -> primeiro -> proximo;
    lista -> quantidade--;
    free(ptr -> no);
    free(ptr);
}
T_No *Remove_ultimo_elemento(T_Lista *lista){
    T_No *no = lista -> primeiro -> no;
    free(lista -> primeiro -> no);
    free(lista -> primeiro);
    lista -> quantidade--;
    return no;
}

T_No *Cria_huffman(T_Lista *lista){
    while(lista -> quantidade > 1){
        Mostra_lista(lista);
        printf("\n");
        Remove_elemento(lista);
        Ordena_lista(lista);
    }
    return Remove_ultimo_elemento(lista);
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