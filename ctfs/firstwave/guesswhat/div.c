#include <stdio.h>
#include <openssl/bn.h>

int main() {
    // Initialize BIGNUM variables
    BIGNUM *dividend = BN_new();
    BIGNUM *divisor = BN_new();
    BIGNUM *quotient = BN_new();
    BIGNUM *remainder = BN_new();

    // Convert hexadecimal strings into BIGNUM objects
    if (!BN_hex2bn(&dividend, "009eee82dc2cd4a00c4f5a7b8663b0c1ed0677fcebde1a235df4c3ff876a7dadc607faa835f6ae0503573e223676d50d574f99f958ad637ae745a6aafa023423b69d34157b1141b6b1cab91acd2955bd42f504abdf454a9d4eca4e01f9f8745967eeb6a9fb96b7c09400178a530eb6d831c968e66438d3633a04d7886bf0e1ad607f41bd857bd904e1975b1f9b05ceac2cc4553fb48b894d0a509a094e5e8f5b5f5569725f049b3a8a09b47f8db2ca520e5ebff4b0eec9badc934f6dd31f821ad9fc2ca73f18230dd744c728546784ee739265f01ce81e6d4d9565b4c84fb80462582bee3264a0a7dc99250e505376bc30db715e93d69f1f881c765d82c8593951")) {
        printf("Error converting hexadecimal string to dividend BIGNUM\n");
        return 1;
    }
    if (!BN_hex2bn(&divisor, "00d2c601326b4c4b855f527bb78ed68ae4c8767e6bc9249a3ecacd2fc9b875d4f97111e1cfbe62d32c5ff9fd9bfaed62f3df44c757fbee9bb232cb5449296c692e301d8c1ffab18ee44966c1fb927c82ca60c940a40ab2db50ecf6ff98a71623388d06d27ca9858ac22b4dd4e6f189e5b04254a05f3cddc764330511fbee8b2607")) {
        printf("Error converting hexadecimal string to divisor BIGNUM\n");
        return 1;
    }

    // Perform division operation
    if (!BN_div(quotient, remainder, dividend, divisor, BN_CTX_new())) {
        printf("Error performing division\n");
        return 1;
    }

    // Convert quotient and remainder to hexadecimal strings
    char *quotient_hex = BN_bn2hex(quotient);
    char *remainder_hex = BN_bn2hex(remainder);
    if (!quotient_hex || !remainder_hex) {
        printf("Error converting quotient or remainder to hexadecimal string\n");
        return 1;
    }

    // Output the quotient and remainder
    printf("Quotient: %s\n", quotient_hex);
    printf("Remainder: %s\n", remainder_hex);

    // Free allocated memory
    BN_free(dividend);
    BN_free(divisor);
    BN_free(quotient);
    BN_free(remainder);
    OPENSSL_free(quotient_hex);
    OPENSSL_free(remainder_hex);

    return 0;
}
