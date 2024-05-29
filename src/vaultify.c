#include "vaultify.h"
#include "encryption.h"
#include "entry.h"
#include <stdlib.h>

encrypted_entry
vlt_encrypt_entry (vlt_entry *entry, const char *password)
{
  encrypted_entry encrypted = { 0 };

  generate_salt (encrypted.iv, SALT_SIZE);

  auto entry_str = vlt_stringfy_entry (entry);
  auto ciphertext_len = 0;
  unsigned char *ciphertext = nullptr;
  vlt_encrypt (entry_str, password, encrypted.iv, &ciphertext,
               &ciphertext_len);
  free (entry_str);

  encrypted.ciphertext = ciphertext;
  encrypted.ciphertext_len = ciphertext_len;
  return encrypted;
}

vlt_entry
vlt_decrypt_entry (encrypted_entry *encrypted, const unsigned char *password)
{
  vlt_entry entry = { 0 };
  unsigned char *plaintext = nullptr;
  vlt_decrypt (encrypted->ciphertext, encrypted->ciphertext_len, password,
               encrypted->iv, &plaintext);
  vlt_replace_from_str (&entry, (char *)plaintext);
  return entry;
}
