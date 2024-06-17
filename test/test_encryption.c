#include "stdlib.h"
#include "string.h"
#include "unity.h"
#include "vaultify.h"
#include <stdio.h>

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

vlt_entry *e;
void
setUp (void)
{
  e = vlt_entry_new ();
}

void
tearDown (void)
{
  vlt_entry_dtr (e);
  e = nullptr;
}

void
test_stringfy_entry ()
{
  vlt_entry_ctr (e, "home", "user", "password");
  char *output = vlt_stringfy_entry (e);
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("home#user#password", output, strlen (output));
  free (output);
}
void
test_split_str_entry ()
{
  vlt_replace_from_str (e, "home#user#password");
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("home", e->url, strlen ("home"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("user", e->username, strlen ("user"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("password", e->password, strlen ("password"));
}

void
test_fixed_encryption ()
{

  unsigned char key[]
      = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30,
          0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
          0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31 };

  /* A 128 bit IV */
  unsigned char iv[] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                         0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35 };
  /* Message to be encrypted */
  const char *plaintext = "The quick brown fox jumps over the lazy dog";
  unsigned char *ciphertext = nullptr;
  int cipher_len;

  vlt_encrypt (plaintext, key, iv, &ciphertext, &cipher_len);

  char *decrypted_text = nullptr;
  vlt_decrypt (ciphertext, cipher_len, key, iv, &decrypted_text);
  TEST_ASSERT_EQUAL_CHAR_ARRAY (plaintext, decrypted_text,
                                strlen (decrypted_text));
}

void
test_generated_encryption ()
{

  unsigned char key[] = "randompassword";
  unsigned char iv[IV_SIZE] = { 0 };

  generate_salt (iv, IV_SIZE);

  const char *plaintext = "hellow#world#here";
  unsigned char *ciphertext = nullptr;
  int cipher_len;

  vlt_encrypt (plaintext, key, iv, &ciphertext, &cipher_len);

  char *decrypted_text = nullptr;
  vlt_decrypt (ciphertext, cipher_len, key, iv, &decrypted_text);
  TEST_ASSERT_EQUAL_CHAR_ARRAY (plaintext, decrypted_text,
                                strlen (decrypted_text));
}
void
test_vlt_encryption ()
{
  vlt_entry_ctr (e, "home", "user", "password");
  auto encrypted = vlt_encrypt_entry (e, "mypassword");
  auto decrypted = vlt_decrypt_entry (&encrypted, "mypassword");
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("home", decrypted.url, strlen ("home"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("user", decrypted.username, strlen ("user"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("password", decrypted.password,
                                strlen ("password"));
}

