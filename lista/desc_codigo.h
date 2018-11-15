#ifndef __desc_codigo__
#define __desc_codigo__
#include "arvore.h"

typedef struct Codigo_do_caractere {
    char letra;
    int codigo[15];
    int tamanho_codigo;
}  T_Codigo_Char;
typedef struct Decodifica_caractere {
    char letra;
    int codigo[15];
    int tamanho_codigo;
    int foi;
}  T_Decodigo_Char;

int Le_tabela(char tabela[], T_Codigo_Char cod[]);
void Passo_descompressao(char huff[], char tabela[]);
int Remonta_texto(T_Decodigo_Char decod[], int codigo[], int n, int tamanho_codigo);
void Passo_descompressao(char huff[], char tabela[]);



#endif