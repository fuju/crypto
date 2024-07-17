#include <stdio.h>

#include <openssl/evp.h>

#include <string.h>

#define ENCRYPT 1
#define DECRYPT 0


int main(){

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    unsigned char key[] = "1234567890abcdef"; //ASCII chars
    unsigned char iv[] = "fedbc0987654321";

    EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, ENCRYPT);

    unsigned char plaintext[] = "Gianluca non sa usare linux."; // 29 bytes
    unsigned char ciphertext[32];

    int lentgh;
    int ciphertext_len=0;
    EVP_CipherUpdate(ctx, ciphertext, &lentgh, plaintext, strlen(plaintext));

    printf("After update: %d\n",lentgh);
    ciphertext_len+=lentgh;

    EVP_CipherFinal(ctx, ciphertext+ciphertext_len, &lentgh);
    printf("After final: %d\n",lentgh);

    EVP_CIPHER_CTX_free(ctx);

    printf("size of the ciphertext = %d\n", ciphertext_len);
    for(int i=0; i<ciphertext_len; i++){
        printf("%02x-", ciphertext[i]);
    }
    printf("\n");

    return 0;

}