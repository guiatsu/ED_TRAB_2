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
void Imprimir_Em_Ordem(T_No *no){
	if(no -> esquerda != NULL){
		Imprimir_Em_Ordem(no -> esquerda);
	}
	Imprimir_No(no);
	if(no -> direita != NULL){
		Imprimir_Em_Ordem(no -> direita);
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
