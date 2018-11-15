#include <stdio.h>
#include <stdlib.h>
#include "desc_codigo.h"
int main(int argc, char **argv){
    if(argc < 2){
        printf("quantidade de arquivos insuficientes\n");
        return 0;
    }
    Passo_descompressao(argv[2],argv[1]);





    return 0;
}