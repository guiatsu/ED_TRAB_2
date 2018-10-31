#ifndef lista
#define lista
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
void Ordena_lista(T_Lista *lista);





#endif