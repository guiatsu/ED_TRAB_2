#ifndef __arvore__
#define __arvore__


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

void Libera_arvore(T_No *no);
void Imprimir_No(T_No *no);

void Imprimir_Pre_Ordem(T_No *no);
void Imprimir_Em_Ordem(T_No *no);


T_No *Aloca_no();


#endif
