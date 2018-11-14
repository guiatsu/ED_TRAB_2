#include <stdio.h>
int main(){
    int a[] = {1,1,1};
    int b[] = {1,0,0};
    int c[] = {1,0};
    int d = 0;
    int i;
    for(i = 0; i < 3; i++){
        d |= a[i];
        d = d << 1;
    }
    for(i = 0; i < 3; i++){
        d |= b[i];
        d = d << 1;
    }
    for(i = 0; i < 2; i++){
        d |= c[i];
        if(i <1){
            d = d << 1;
        }
        
    }
    FILE *fd;
    fd = fopen("teste.bin", "wb");
    fwrite(&d,1,1,fd);


    return 0;
}

