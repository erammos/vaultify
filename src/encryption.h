#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H
#if !defined(_VLT_H_INSIDE) && !defined(VLT_COMPILATION)
#error "Only <vaultify.h> can be included directly."
#endif
#define SALT_SIZE 16
#define KEY_SIZE 32
#define IV_SIZE 128
#define ITERATIONS 10000
int generate_salt (unsigned char *salt, int size);
int derive_key_iv (const char *password, unsigned char *salt,
                   unsigned char *key, unsigned char *iv);
int vlt_encrypt (const char *plaintext, const unsigned char *key,
                 const unsigned char *iv, unsigned char **ciphertext,
                 int *ciphertext_len);
int vlt_decrypt (unsigned char *ciphertext, int ciphertext_len,
                 const unsigned char *key, const unsigned char *iv,
                 unsigned char **plaintext);
#endif