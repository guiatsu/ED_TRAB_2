#ifndef __codigo__
#define __codigo__
#include "arvore.h"

typedef struct Codigo_do_caractere {
    char letra;
    int codigo[15];
    int tamanho_codigo;
}  T_Codigo_Char;

void Monta_codigo(T_No *no, int vet[],T_Codigo_Char cod[], int n, FILE *fd);

void Verifica_ocorrencia(T_Ascii ascii[], unsigned char texto[], int n);
int Bubblesort(T_Ascii vet[], int fim);
int Verifica_tamanho_arquivo(unsigned char arquivo[]);
void Le_arquivo(unsigned char vet[], int n, unsigned char arquivo[]);

void Passo_a_passo(unsigned char arquivo[]);







#endif