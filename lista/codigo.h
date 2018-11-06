#ifndef __codigo__
#define __codigo__
#include "arvore.h"


void Monta_codigo(T_No *no, int vet[], int n, FILE *fd);

void Verifica_ocorrencia(T_Ascii ascii[], char texto[], int n);
int Bubblesort(T_Ascii vet[], int fim);
int Verifica_tamanho_arquivo(char arquivo[]);
void Le_arquivo(char vet[], int n, char arquivo[]);

void Passo_a_passo(char arquivo[], char arquivo_tabela[]);







#endif