#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "codigo.h"

void Monta_codigo(T_No *no, int vet[],T_Codigo_Char cod[], int n, FILE *fd){
    if(no -> esquerda != NULL){
        vet[n] = 0;
		Monta_codigo(no -> esquerda, vet,cod, n+1, fd);
	}
	if(no -> direita != NULL){
        vet[n] = 1;
		Monta_codigo(no -> direita, vet,cod, n+1, fd);
	}
    if(no -> esquerda == NULL && no -> direita == NULL){
        int i;
        fprintf(fd,"%c: ", no -> dados -> letra);
        for(i = 0; i < n; i++){
            fprintf(fd, "%d", vet[i]);
            cod[no -> dados -> letra].letra = no -> dados -> letra;
            cod[no -> dados -> letra].codigo[i] = vet[i];
        }
            cod[no -> dados -> letra].tamanho_codigo = n;
        fprintf(fd,"\n");
    }

}
void escreve_binario(unsigned char c,int final, T_Codigo_Char vet[]){
    static int cont = 0;
    static unsigned char buffer = 0;
    int i;
    FILE *fd;
    fd = fopen("myfile.huff","ab");
    if(final == FALSE){
        for(i = 0; i < vet[c].tamanho_codigo; i++){
            buffer |= vet[c].codigo[i];
            cont++;
            printf("buffer: %d\ncont: %d\n", buffer, cont);
            if(cont == 8){
                fwrite(&buffer,1,1,fd);
                buffer = 0;
                cont = 0;
            }
            buffer = buffer << 1;
            printf("buffer: %d\ncont: %d\n", buffer, cont);
        }
    }
    else{
        for(i = 0; i < vet[c].tamanho_codigo; i++){
            buffer |= vet[c].codigo[i];
            printf("buffer: %d\ncont: %d\n", buffer, cont);
            cont++;
            if(cont == 8){
                fwrite(&buffer,1,1,fd);
                buffer = 0;
                cont = 0;
            }
            buffer = buffer << 1;
            printf("buffer: %d\ncont: %d\n", buffer, cont);
        }
        if(cont != 0){
            buffer = buffer << (8-(cont+1));
            printf("buffer: %d\ncont: %d\n", buffer, cont);
            cont = 8-cont;
            printf("cont_f: %d\n", cont);
            fwrite(&buffer,1,1,fd);

        }
    }
    fclose(fd);
}

void Verifica_ocorrencia(T_Ascii ascii[], unsigned char texto[], int n){     // funcao que verifica se tem ocorrencia de um caractere e quantas vezes ele ocorre
    int i;
    for(i = 0; i < n; i++){
        ascii[texto[i]].frequencia++;                          // para cada caractere encontrado, incrementar um na posicao referente a tabela ascii
        ascii[texto[i]].letra = texto[i];
    }
}
int Bubblesort(T_Ascii vet[], int fim){
    int i,j = 0,trocou = TRUE;
    T_Ascii aux;
    while(trocou == TRUE){
        trocou = 0;
        for(i = 0; i < fim -1 -j; i++){
            if(vet[i].frequencia > vet[i+1].frequencia){
                aux.frequencia = vet[i].frequencia;
                aux.letra = vet[i].letra;

                vet[i].frequencia = vet[i+1].frequencia;
                vet[i].letra = vet[i+1].letra;

                vet[i+1].frequencia = aux.frequencia;
                vet[i+1].letra = aux.letra;

                trocou = 1;
            }
        }
        j++;
    }     
}
int Verifica_tamanho_arquivo(unsigned char arquivo[]){       // funcao que abre o arquivo no final e verifica quantos bytes estao contidos nele
    FILE *fd;                                       // descritor do arquivo
    int tam;                                        // variavel pra guardar o tamanho do arquivo
    fd = fopen(arquivo, "a");                       // abrindo o arquivo com descritor apontando para o final dele
    tam = ftell(fd);                                // pega quantos bytes se passaram ate a posicao atual no arquivo
    fclose(fd);                                     // fecha o arquivo
    return tam;
}
void Le_arquivo(unsigned char vet[], int n, unsigned char arquivo[]){ // funcao que passa o que estah escrito no arquivo de texto para um vetor
    FILE *fd;                                       // descritor do arquivo
    int i;
    fd = fopen(arquivo, "r");                       // abrindo o arquivo para leitura
    for(i = 0; i < n ; i++){
        fscanf(fd,"%c", &vet[i]);                   // atribuindo cada um dos caracteres para uma posicao do vetor
    }
    fclose(fd);                                     // fechando o arquivo
}

void Passo_a_passo(unsigned char arquivo[]){                 // funcao responsavel por rodar o codigo
    int tam = Verifica_tamanho_arquivo(arquivo);
    unsigned char string[tam];                               // vetor para guardar o texto retirado do arquivo original
    int i, qtd_arvores;
    T_Lista *lista;
    T_No *huff;         // no onde ficara salvo a arvore de huffman
    lista = Aloca_lista();
    T_Ascii ascii[256];   // vetor para guarda em cada posicao se o caractere esta presente no vetor e quantas vezes aparece
    T_Codigo_Char cod[256];
    FILE *fd;
    for(i = 0; i < 256; i++){
        ascii[i].frequencia = 0;
        ascii[i].letra = i;
    }
    for(i = 0; i < 256; i++){
        cod[i].letra = '\0';
        cod[i].tamanho_codigo = 0;
        for(int j = 0; j < 15;j++){
            cod[i].codigo[j] = 0;
        }
    }
    Le_arquivo(string, tam, arquivo);
    Verifica_ocorrencia(ascii, string, tam);
    Bubblesort(ascii, 256);
    for(i = 0; i < 256; i ++){
        printf("%d: %c %d\n", ascii[i].letra, ascii[i].letra, ascii[i].frequencia);
    }
    for(i = 0; i < 256; i++){
        if(ascii[i].frequencia != 0){
            Aloca_elemento(lista);
            lista -> ultimo -> no -> dados -> frequencia = ascii[i].frequencia;
            lista -> ultimo -> no -> dados -> tamanho = 1;
            lista -> ultimo -> no -> dados -> letra = ascii[i].letra;
        }
    }
    Aloca_elemento(lista);
    lista -> ultimo -> no -> dados -> frequencia = 1;
    lista -> ultimo -> no -> dados -> tamanho = 1e6;
    lista -> ultimo -> no -> dados -> letra = '\0';
    huff = Cria_huffman(lista);
    free(lista);
    Imprimir_Em_Ordem(huff);
    fd = fopen("tabela.txt", "w");
    int vet[huff -> dados -> tamanho];
    Monta_codigo(huff, vet,cod, 0, fd);
    fclose(fd);
    fd = fopen("myfile.huff","wb");
    fclose(fd);
    for( i = 0; i < tam; i++){
        escreve_binario(string[i],0,cod);
    }
    escreve_binario('\0',1,cod);
    Libera_arvore(huff);

}