#include "vaultify.h"
#include "encryption.h"
#include "entry.h"
#include <stdlib.h>
#include <string.h>

static const char *urls[MAX_URL] = { 0 };
static size_t url_len;
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
size_t
vlt_get_list_by_url (const char **list[])
{
  vlt_entry **entries;
  size_t length = get_entries (&entries);
  for (size_t i = 0; i < length; i++)
    {
      urls[i] = entries[i]->url;
    }
  *list = urls;

  return length;
}
static bool cmp_url(void * url1, void * url2)
{
  return strcmp(url1,url2) == 0;
}
vlt_entry * vlt_get_entry_by_url (char url[])
{

  vlt_entry **entries;
  size_t length = get_entries (&entries);
  for (size_t i = 0; i < length; i++)
    {
      if ( strcmp(entries[i]->url,url) == 0 )
      {
        return entries[i];
      }
    }
    return nullptr;
}
