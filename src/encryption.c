#include "encryption.h"
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
generate_salt (unsigned char *salt, int size)
{
  if (!RAND_bytes (salt, size))
    {
      ERR_print_errors_fp (stderr);
      return 0;
    }
  return 1;
}

int
derive_key_iv (const char *password, unsigned char *salt, unsigned char *key,
               unsigned char *iv)
{
  if (!PKCS5_PBKDF2_HMAC_SHA1 (password, strlen (password), salt, SALT_SIZE,
                               ITERATIONS, KEY_SIZE, key))
    {
      ERR_print_errors_fp (stderr);
      return 0;
    }
  if (!RAND_bytes (iv, IV_SIZE))
    {
      ERR_print_errors_fp (stderr);
      return 0;
    }
  return 1;
}
int
vlt_encrypt (const char *plaintext, const unsigned char *key,
             const unsigned char *iv, unsigned char **ciphertext,
             int *ciphertext_len)
{
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new ();
  if (!ctx)
    {
      ERR_print_errors_fp (stderr);
      return 0;
    }

  if (!EVP_EncryptInit_ex (ctx, EVP_aes_256_cbc (), NULL, key, iv))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      return 0;
    }

  int len;
  *ciphertext = malloc (strlen (plaintext)
                        + EVP_CIPHER_block_size (EVP_aes_256_cbc ()));
  if (!*ciphertext)
    {
      EVP_CIPHER_CTX_free (ctx);
      return 0;
    }

  if (!EVP_EncryptUpdate (ctx, *ciphertext, &len, (unsigned char *)plaintext,
                          strlen (plaintext)))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      free (*ciphertext);
      return 0;
    }
  *ciphertext_len = len;

  if (!EVP_EncryptFinal_ex (ctx, *ciphertext + len, &len))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      free (*ciphertext);
      return 0;
    }
  *ciphertext_len += len;

  EVP_CIPHER_CTX_free (ctx);
  return 1;
}

int
vlt_decrypt (unsigned char *ciphertext, int ciphertext_len,
         const unsigned char *key, const unsigned char *iv,
         unsigned char **plaintext)
{
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new ();
  if (!ctx)
    {
      ERR_print_errors_fp (stderr);
      return 0;
    }

  if (!EVP_DecryptInit_ex (ctx, EVP_aes_256_cbc (), NULL, key, iv))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      return 0;
    }

  int len;
  *plaintext
      = malloc (ciphertext_len + EVP_CIPHER_block_size (EVP_aes_256_cbc ()));
  if (!*plaintext)
    {
      EVP_CIPHER_CTX_free (ctx);
      return 0;
    }

  if (!EVP_DecryptUpdate (ctx, *plaintext, &len, ciphertext, ciphertext_len))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      free (*plaintext);
      return 0;
    }
  int plaintext_len = len;

  if (!EVP_DecryptFinal_ex (ctx, *plaintext + len, &len))
    {
      ERR_print_errors_fp (stderr);
      EVP_CIPHER_CTX_free (ctx);
      free (*plaintext);
      return 0;
    }
  plaintext_len += len;

  (*plaintext)[plaintext_len] = '\0'; // Null-terminate the decrypted string

  EVP_CIPHER_CTX_free (ctx);
  return plaintext_len;
}
