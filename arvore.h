#ifndef arvore
#define arvore

typedef struct Dados {
    int frequencia;
    char letra;
    int tamanho;
    
} T_Dados;

typedef struct No {
    struct No *esquerda;
    struct No *direita;
    T_Dados *dados;
} T_No;

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




typedef struct Ascii {
    int frequencia;
    char letra;
}T_Ascii;




#define TRUE 1
#define FALSE 0


T_No *Aloca_no();
void Verifica_ocorrencia(T_Ascii ascii[], char texto[], int n);
int Quicksort(T_Ascii vet[], int inicio, int fim);
void Le_arquivo(char vet[], int n, char arquivo[]);
int Verifica_tamanho_arquivo(char arquivo[]);
void Passo_a_passo(char arquivo[]);


int Lista_vazia(T_Lista *lista);
T_Lista *Aloca_lista();
T_Elemento *Aloca_elemento(T_Lista *lista);
void Ordena_lista(T_Lista *lista);





#endif