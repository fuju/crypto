#include <stdio.h>
#include <openssl/bn.h>

int main ()
{
  char hex_string[] = "11111111111111111111111111111111";
  char hex_string2[] = "22222222222222222222222222222222";
  char hex_string3[] = "3333";
  char hex_string4[] = "2341234123412341234";

  BIGNUM *a = BN_new();
  BN_hex2bn(&a, hex_string);
  BIGNUM *b = BN_new();
  BN_hex2bn(&b, hex_string2);
  BIGNUM *c = BN_new();
  BN_hex2bn(&c, hex_string);
  BIGNUM *d = BN_new();
  BN_hex2bn(&d, hex_string2);

  // add two numbers
  BIGNUM *res=BN_new();
  BN_add(res,a,b);
  // BN_add(a,a,b);
  BN_print_fp(stdout,res);
  puts("");
  printf("%lu\n",BN_get_word(res));
  /*
  int BN_mod_exp(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
         const BIGNUM *m, BN_CTX *ctx);
  */
  BIGNUM *m=BN_new();
  BN_set_word(m,35);
  // a^b mod m
  if (!BN_mod_exp(res,a,b,m,ctx)) {
    ERR_print_errors_fp(stdout);
    exit(1);
  }

  BN_print_fp(stdout,res);
  puts("");

  /*
  int BN_cmp(BIGNUM *a, BIGNUM *b);
  int BN_ucmp(BIGNUM *a, BIGNUM *b);
  */
  int cmp_result;
  cmp_result = BN_cmp(a,b);
  if(cmp_result == 0)
    printf("=\n");
  else if (cmp_result <0)
    printf("<\n");
  else
    printf(">\n");

  return 0;
}