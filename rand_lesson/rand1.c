#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#define MAX 128

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main(){

    unsigned char random_string[MAX];

    //initialization of seed
    if ( RAND_load_file("/dev/random",64) != 64 )
        handle_errors();
        //fprintf(stderr, "Error with the initialization of the PRNG\n");

    //RAND_bytes() and RAND_priv_bytes() returns 1 on success, -1 if not supported by the current RAND method,
    // or 0 on other failure

    //generate rand bytes and prints it
    if( RAND_bytes(random_string, MAX) != 1 )
        handle_errors();

    for(int i=0;i<MAX;i++){
        printf("%02x-",random_string[i]);
    }

    printf("\n");

    return 0;
}