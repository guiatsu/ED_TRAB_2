#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"


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