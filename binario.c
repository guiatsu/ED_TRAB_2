/*EXEMPLO DE COMO ESCREVER NUM ARQUIVO NUMEROS BINARIOS DE TAMANHO DIFERENTE A MULTIPLOS DE 8*/

#include <stdio.h>
#include <stdlib.h>
#define BITS 12 /* numero de bits de cada palavra*/
#define MAX_VALUE (1 << BITS) - 1 /* valor maximo da palabra do tamanho definido */

void escrever_binario(FILE *output,unsigned int code);
unsigned int ler_binario(FILE *input);

int main()
{
    int i,in[5],out[5];
    FILE *f1;
    char nome1[]="Meuarquivo.bin";
    
    f1 = fopen(nome1,"w+b");
    printf("Escreve 5 numeros inteiros a serem representadados com %d bits",BITS);
    for (i=0;i<5;i++) 
    {
        printf("\n%d: ",i+1);
        scanf("%d",&in[i]);
        escrever_binario(f1,in[i]);
    } 
    /* O valor maximo pode ser utilizada para indicar final de transmiss�o, nesse exemplo sabemos que s�o 5 valores */
    escrever_binario(f1,MAX_VALUE); 
    escrever_binario(f1,0); /* esvaziar o buffer (pode que n�o seja suficiente, o mlehor seria fazer uma fun��o que verifique se o buffer esta vazio ou n�o e escreva ele caso n�o esteja*/
    fclose(f1);
    f1 = fopen(nome1,"r+b");
    printf("Lendo o arquivo gerado...");
    i = 0;
    while ((out[i] = ler_binario(f1))!=(MAX_VALUE))
        printf("\n%d: %d",i+1,out[i]);

    getchar();
    getchar();
}

void escrever_binario(FILE *output,unsigned int code){
    static int output_bit_count=0;
    static unsigned long output_bit_buffer=0L;

    output_bit_buffer |= (unsigned long) code << (32-BITS-output_bit_count);
    output_bit_count += BITS;
    while (output_bit_count >= 8){
        putc(output_bit_buffer >> 24,output);
        output_bit_buffer <<= 8;
        output_bit_count -= 8;
    }
}


unsigned int ler_binario(FILE *input){
    unsigned int return_value;
    static int input_bit_count=0;
    static unsigned long input_bit_buffer=0L;

    while (input_bit_count <= 24){
        input_bit_buffer |= 
        (unsigned long) getc(input) << (24-input_bit_count);
        input_bit_count += 8;
    }
    return_value=input_bit_buffer >> (32-BITS);
    input_bit_buffer <<= BITS;
    input_bit_count -= BITS;
    return(return_value);
}
