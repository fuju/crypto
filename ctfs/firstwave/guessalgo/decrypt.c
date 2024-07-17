#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int decrypt_file(const char *input_file, const char *output_file, const unsigned char *key, const unsigned char *iv, const char *algo) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "ab");
    FILE *out_filenb = fopen(output_file, "a");

    if (!in_file || !out_file) {
        perror("Error opening files");
        return 1;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        perror("Error creating cipher context");
        return 1;
    }

    EVP_CIPHER_CTX_init(ctx);
    if (EVP_DecryptInit_ex(ctx, EVP_get_cipherbyname(algo), NULL, key, iv) != 1) {
        perror("Error initializing decryption");
        return 1;
    }

    const int BUFFER_SIZE = 1024;
    unsigned char buffer[BUFFER_SIZE];
    int len;
    int ciphertext_len = 0;

    while ((len = fread(buffer, 1, BUFFER_SIZE, in_file)) > 0) {
        if (EVP_DecryptUpdate(ctx, buffer, &len, buffer, len) != 1) {
            perror("Error decrypting");
            return 1;
        }
        fwrite(buffer, 1, len, out_file);
        ciphertext_len += len;
    }

    if (EVP_DecryptFinal_ex(ctx, buffer, &len) != 1) {
        perror("Error finalizing decryption");
        return 1;
    }

    fwrite(buffer, 1, len, out_file);
    fwrite("\n",1,1,out_file);
    fwrite(algo,1, strlen(algo), out_filenb);
    fwrite("\n",1,1,out_filenb);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    fclose(in_file);
    fclose(out_file);
    fclose(out_filenb);

    printf("Decryption successful! Wrote %d bytes.\n", ciphertext_len);

    return 0;
}

int main(int argc, char **argv) {
    const char *input_file = "file2.enc";
    const char *output_file = "decrypted_file.txt";

    // Replace these with your actual key and IV
    unsigned char key[] = "0123456789ABCDEF";
    unsigned char iv[] = "0123456789ABCDEF";

    if (decrypt_file(input_file, output_file, key, iv, argv[1]) != 0) {
        printf("Decryption failed.\n");
        return 1;
    }

    return 0;
}
