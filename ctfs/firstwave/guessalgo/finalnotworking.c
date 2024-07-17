#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/err.h>


#define ENCRYPT 1
#define DECRYPT 0
#define MAX_BUFFER 1024

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char **argv)
{

//  int EVP_CipherInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv, int enc);
//  int EVP_CipherUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl);
//  int EVP_CipherFinal(EVP_CIPHER_CTX *ctx, unsigned char *outm, int *outl);




    if(argc != 6){
        fprintf(stderr,"Invalid parameters. Usage: %s file_in key iv file_out algo\n",argv[0]);
        exit(1);
    }
    printf("algo is: %s--",argv[5]);

    FILE *f_in;
    if((f_in = fopen(argv[1],"r")) == NULL) {
            fprintf(stderr,"Couldn't open the input file, try again\n");
            abort();
    }
    
    FILE *f_out;
    if((f_out = fopen(argv[4],"a")) == NULL) { //i think the error is also here, ab not only a
            fprintf(stderr,"Couldn't open the output file, try again\n");
            abort();
    }

    unsigned char key[strlen(argv[2])/2];
    for(int i = 0; i < strlen(argv[2])/2;i++){
        sscanf(&argv[2][2*i],"%2hhx", &key[i]);
    }

    unsigned char iv[strlen(argv[3])/2];
    for(int i = 0; i < strlen(argv[3])/2;i++){
        sscanf(&argv[3][2*i],"%2hhx", &iv[i]);
    }

    /* Load the human readable error strings for libcrypto */
    ERR_load_crypto_strings();
    /* Load all digest and cipher algorithms */
    OpenSSL_add_all_algorithms();



    // pedantic mode: check NULL
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if(!EVP_CipherInit(ctx,EVP_get_cipherbyname(argv[5]), key, iv, DECRYPT))
        handle_errors();

    int length;
    unsigned char ciphertext[MAX_BUFFER+16];

    int n_read;
    unsigned char buffer[MAX_BUFFER];
    unsigned char output[MAX_BUFFER+30+16];
    strcat(output, "\ntry with algo ");
    strcat(output, argv[5]);
    strcat(output, ": ");

    while((n_read = fread(buffer,1,MAX_BUFFER,f_in)) > 0){
        printf("n_Read=%d-",n_read);
        if(!EVP_CipherUpdate(ctx,ciphertext,&length,buffer,n_read)){
            strcpy(output,"error!");
            handle_errors();
        }
        printf("length1=%d\n",length);
        strcat(output, ciphertext);
    }

    if(!EVP_CipherFinal(ctx,ciphertext+length,&length))
        handle_errors();

    strcat(output, ciphertext);
    printf("lenght2=%d\n",length);
    if(fwrite(output,1, strlen(output), f_out) < 0){
        fprintf(stderr,"Error writing in the output file\n");
        abort();
    }

    EVP_CIPHER_CTX_free(ctx);

    fclose(f_in);
    fclose(f_out);

    printf("File encrypted!, %s\n--------------------\n\n",ciphertext);

    // completely free all the cipher data
    CRYPTO_cleanup_all_ex_data();
    /* Remove error strings */
    ERR_free_strings();

    return 0;
}

