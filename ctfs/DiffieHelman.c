/*
    void send_to_sara(BIGNUM b)
    BIGNUM receive_from_sara()
    void send_to_carl(BIGNUM b)
    BIGNUM receive_from_carl()
*/

#include <openssl/evp.h>
#include <openssl/bn.h>

int main(int argc, char** argv[]){

    BIGNUM *p = BN_new(); //first prime factor
    BIGNUM *q = BN_new(); //second prime factor
    BIGNUM *m = BN_new(); // p*q

    BIGNUM *g = BN_new(); //generatore modulo p
    BIGNUM *k = BN_new(); //shared key

    BIGNUM *a = BN_new(); //secret

    BN_rand(a,1022,0,1);


    BIGNUM *A = BN_new();

    BN_CTX *ctx=BN_CTX_new();

    BN_generate_prime_ex(p, 1024, 1, NULL, NULL, NULL);
    BN_generate_prime_ex(q, 1024, 1, NULL, NULL, NULL);
    BN_mul(m,p,q,ctx);

    //generate g (not correct)
    BN_generate_prime_ex(g, 1024, 1, NULL, NULL, NULL);

    //A = g^a mod p
    BN_mod_exp(A, g, a, p, ctx);

    printf("p=");
    BN_print_fp(stdout,p);
    printf("\n");
    printf("q=");
    BN_print_fp(stdout,q);
    printf("\n");
    printf("m=");
    BN_print_fp(stdout,m);
    printf("\n");
    printf("g=");
    BN_print_fp(stdout,g);
    printf("\n");
    printf("A=");
    BN_print_fp(stdout,A);
    printf("\n");

    // send_to_sara(p);
    // send_to_sara(g);
    // send_to_sara(A);

    // BIGNUM *B = receive_from_sara();

    // BN_mod_exp(k, B, a, p, ctx);

    // (g^b)^a mod p = (g^a)^b mod p

}