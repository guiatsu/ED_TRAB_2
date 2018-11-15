#ifndef __lista__
#define __lista__
#include "arvore.h"
typedef struct Elemento {
    struct Elemento *proximo;
    struct Elemento *anterior;
    T_No *no;

}T_Elemento;

typedef struct Lista {
    T_Elemento *primeiro;
    T_Elemento *ultimo;
    int quantidade;
}T_Lista;

int Lista_vazia(T_Lista *lista);
T_Lista *Aloca_lista();

T_Elemento *Aloca_elemento(T_Lista *lista);
void Remove_elemento(T_Lista *lista);

void Mostra_lista(T_Lista *lista);
T_No *Cria_huffman(T_Lista *lista);




#endif