#include <stdio.h>
#include <stdlib.h>
#include "desc_codigo.h"
int Le_tabela(char tabela[], T_Codigo_Char cod[]){
    FILE *fd;
    unsigned char letra;
    int i = 0, cont = 0;
    char valor[1];
    fd = fopen(tabela, "r");
    while(fscanf(fd,"%c: ", &letra) != EOF){
        cod[letra].letra = letra;
        do{
            fscanf(fd,"%c", &valor[0]);
            if(valor[0] != '\n'){
                cod[letra].codigo[i] = atoi(valor);
                cod[letra].tamanho_codigo++;
                i++;
            }
        }while(valor[0] != '\n');
        i = 0;
        cont++;
    }
    fclose(fd);
    return cont;
}
void Le_binario(char huff[],int codificado[], int n){
    unsigned char buffer = 0;
    int cont = 0;
    int i,j;
    FILE *fd;
    fd = fopen(huff, "ab");
    int tamanho = ftell(fd);
    fclose(fd);
    fd = fopen(huff, "rb");
    for(i = 1; i <= tamanho; i++){
        fread(&buffer,1,1,fd);
        for(j = (((n/tamanho)*i)-1);j >= (((n/tamanho)*i)-8);j--){
            codificado[j] = ((buffer >> cont) & 1);

            printf("aux: %d | ",codificado[j]);
            printf("j: %d\n", j);
            cont ++;
        }
        cont = 0;
    }
    for(i = 0; i < tamanho*8; i++){
        printf("%d",codificado[i]);
    }
    printf("\n");
    fclose(fd);

}
int Remonta_texto(T_Decodigo_Char decod[], int codigo[], int n, int tamanho_codigo){
    int i, j, k;
    int cont = 0;
    FILE *fd;
    fd = fopen("descomprimido.txt", "w");
    int flag = 0;
    for(i = 0;i < tamanho_codigo; i++){
        printf("bit atual: %d | ",codigo[i]);
        for(j = 0;j < n; j++){
            if(decod[j].codigo[cont] == codigo[i]){
                if(flag == 0){
                    if(cont < decod[j].tamanho_codigo){
                        decod[j].foi++;
                    }
                }
                printf("foi: %d | tamanho_codigo: %d | letra: %c\n",decod[j].foi,decod[j].tamanho_codigo,decod[j].letra);
                if(decod[j].foi == decod[j].tamanho_codigo){
                    printf("letra: %c\n", decod[j].letra);
                    if(decod[j].letra != '\0'){
                        fprintf(fd,"%c",decod[j].letra);
                        cont = 0;
                        flag = 1;
                        for(k = 0;k < n; k++){
                            decod[k].foi = 0;
                        }
                    }
                    else{
                        fclose(fd);
                        return 1;
                    }
                }
            }
        }
        if(flag == 0){
            cont++;
        }
        else{
            flag = 0;
        }
    }
    fclose(fd);
    return 1;
}


void Passo_descompressao(char huff[], char tabela[]){
    int i,j;
    T_Codigo_Char cod[256];
    FILE *fd;
    fd = fopen(huff, "ab");
    int tamanho_codigo = ftell(fd)*8;
    int codigo[tamanho_codigo];
    int qtd_codigos, cont = 0;
    fclose(fd);
    for(i = 0;i < 256;i++){
        cod[i].letra = '\0';
        cod[i].tamanho_codigo = 0;
        cod[i].codigo[0] = 0;
    }
    qtd_codigos = Le_tabela(tabela,cod);
    T_Decodigo_Char cod_aux[qtd_codigos];
    for(i = 0;i < 256;i++){
        if(cod[i].tamanho_codigo != 0){
            cod_aux[cont].letra = cod[i].letra;
            cod_aux[cont].tamanho_codigo = cod[i].tamanho_codigo;
            cod_aux[cont].foi = 0;
            printf("letra: %c | tamanho_codigo: %d | codigo: ",cod[i].letra,cod[i].tamanho_codigo);
            for(j = 0;j < cod[i].tamanho_codigo;j++){
                printf("%d", cod[i].codigo[j]);
                cod_aux[cont].codigo[j] = cod[i].codigo[j];
            }
            printf("\n");
            cont++;
        }
    }
    Le_binario(huff,codigo,tamanho_codigo);
    Remonta_texto(cod_aux, codigo, qtd_codigos, tamanho_codigo);
    
}