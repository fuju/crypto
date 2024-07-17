#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#define MAX 128

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(){

    FILE *fp1 = fopen("rand1", "rb");

    FILE *fp2 = fopen("rand2", "rb");

    FILE *foutk1 = fopen("k1", "wb");

    FILE *foutk2 = fopen("k2", "wb");

    // Read and XOR bytes until end of file (EOF) is reached on either file
    unsigned char byte1, byte2;
    while (fread(&byte1, sizeof(char), 1, fp1) != 0 && fread(&byte2, sizeof(char), 1, fp2) != 0) {
        unsigned char k1 = byte1 | byte2;
        unsigned char k2 = byte1 & byte2;
        fwrite(&k1, sizeof(char), 1, foutk1);
        fwrite(&k2, sizeof(char), 1, foutk2);
    }
    fclose(foutk1);
    fclose(foutk2);

    FILE *fp1s = fopen("k1", "rb");

    FILE *fp2s = fopen("k2", "rb");

    FILE *fout = fopen("flag", "wb");

    unsigned char byte3;
    unsigned char byte4;
    while (fread(&byte3, sizeof(char), 1, fp1s) != 0 && fread(&byte4, sizeof(char), 1, fp2s) != 0) {
        unsigned char flag = byte3 ^ byte4;
        printf("%02x-",flag);
        fwrite(&flag, sizeof(char), 1, fout);
    }

    return 0;
}