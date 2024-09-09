#include<stdio.h>
#include<openssl/evp.h>
#include<openssl/err.h>

#define BUFFSIZE 256

void handleErrors(void){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char **argv[]){
    FILE* f_in;
    unsigned char buff[BUFFSIZE];

    int i = 0;
    unsigned char digest[32]; // use the proper constant (256bit/8) //

    EVP_MD_CTX *md = EVP_MD_CTX_new();
    
    EVP_DigestInit(md, EVP_sha256());


    if((f_in = fopen(argv[1],"r")) == NULL) {
            fprintf(stderr,"Couldn't open the input file, try again\n");
            exit(1);
    }

    int n;
    unsigned char buffer[BUFFSIZE];
    while((n = fread(buffer,1,BUFFSIZE,f_in)) > 0){
            EVP_DigestUpdate(md, buffer, n);
    }

    unsigned char md_value[EVP_MD_size(EVP_sha256())]; //32char
    int md_len;

    EVP_DigestFinal_ex(md, md_value, &md_len);

    EVP_MD_CTX_free(md);

    printf("The digest is: ");
    for(int i = 0; i < md_len; i++)
                printf("%02x", md_value[i]);
    printf("\n");

	return 0;
}
