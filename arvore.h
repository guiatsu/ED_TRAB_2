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
    unsigned char letra;
}T_Ascii;




#define TRUE 1
#define FALSE 0

void Imprimir_No(T_No *no);
void Imprimir_Pre_Ordem(T_No *no);
int Lista_vazia(T_Lista *lista);
T_Lista *Aloca_lista();
T_Elemento *Aloca_elemento(T_Lista *lista);
void Ordena_lista(T_Lista *lista);
T_No *Aloca_no();
void Verifica_ocorrencia(T_Ascii ascii[], char texto[], int n);
int Bubblesort(T_Ascii vet[], int fim);
void Le_arquivo(char vet[], int n, char arquivo[]);
int Verifica_tamanho_arquivo(char arquivo[]);
void Remove_elemento (T_Lista *lista);
T_No *Remove_ultimo_elemento (T_Lista *lista);
T_No *Cria_Huffman (T_Lista *lista);
void Passo_a_passo(char arquivo[], char arquivo_tabela[]);




#endif