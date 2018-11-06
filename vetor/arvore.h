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




typedef struct Ascii {
    int frequencia;
    unsigned char letra;
}T_Ascii;




#define TRUE 1
#define FALSE 0

void Imprimir_No(T_No *no);
void Imprimir_Pre_Ordem(T_No *no);
T_No *Aloca_no();
void Verifica_ocorrencia(T_Ascii ascii[], char texto[], int n);
int Bubblesort(T_Ascii vet[], int fim);
void Le_arquivo(char vet[], int n, char arquivo[]);
int Verifica_tamanho_arquivo(char arquivo[]);
void Passo_a_passo(char arquivo[], char arquivo_tabela[]);




#endif