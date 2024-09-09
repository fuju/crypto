#include<stdio.h>
#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/hmac.h>
#include<string.h>

#define BUFFSIZE 256

void handleErrors(void){
    ERR_print_errors_fp(stderr);
    printf(stderr);
    abort();
}

int main(int argc, char **argv[]){
    FILE* f_in;
    unsigned char buff[BUFFSIZE];

    int i = 0;
    unsigned char key[] = "thisismykey";
    EVP_PKEY *hmac_key = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, key, strlen(key));

    EVP_MD_CTX *hmac_ctx = EVP_MD_CTX_new();
    
    if(!EVP_DigestSignInit(hmac_ctx, NULL, EVP_sha256(), NULL, hmac_key))
        handleErrors();


    if((f_in = fopen(argv[1],"r")) == NULL) {
            fprintf(stderr,"Couldn't open the input file, try again\n");
            exit(1);
    }

    int n;
    unsigned char buffer[BUFFSIZE];
    while((n = fread(buffer,1,BUFFSIZE,f_in)) > 0){
        if(!EVP_DigestSignUpdate(hmac_ctx, buffer, n))
            handleErrors();
    }

    unsigned char hmac_value[EVP_MD_size(EVP_sha256())]; //32char
    size_t hmac_len = EVP_MD_size(EVP_sha256());

    EVP_DigestSignFinal(hmac_ctx, hmac_value, &hmac_len);

    printf("The HMAC is: ");
    for(int i = 0; i < hmac_len; i++)
                printf("%02x", hmac_value[i]);
    printf("\n");

    EVP_MD_CTX_free(hmac_ctx);

	return 0;
}
