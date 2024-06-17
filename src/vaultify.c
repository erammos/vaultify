#include "vaultify.h"
#include "encryption.h"
#include "entry.h"
#include <stdio.h>
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
static bool
cmp_url (void *url1, void *url2)
{
  return strcmp (url1, url2) == 0;
}
vlt_entry *
vlt_get_entry_by_url (char url[])
{

  vlt_entry **entries;
  size_t length = get_entries (&entries);
  for (size_t i = 0; i < length; i++)
    {
      if (strcmp (entries[i]->url, url) == 0)
        {
          return entries[i];
        }
    }
  return nullptr;
}

size_t
vlt_get_entries_size ()
{
  vlt_entry **entries;
  size_t length = get_entries (&entries);
  return length;
}

int
vlt_save_entries (const char *filename, const char *key)
{

  vlt_entry **e;
  size_t len = get_entries (&e);

  auto fp = fopen (filename, "wb");
  fwrite (&len, sizeof (size_t), 1, fp);
  for (size_t i = 0; i < len; ++i)
    {
      auto encrypted = vlt_encrypt_entry (e[i], key);
      fwrite (&encrypted.ciphertext_len, sizeof (int), 1, fp);
      fwrite (encrypted.ciphertext, sizeof (unsigned char),
              encrypted.ciphertext_len, fp);
      fwrite (encrypted.iv, sizeof (unsigned char), IV_SIZE, fp);
      fwrite (encrypted.salt, sizeof (unsigned char), SALT_SIZE, fp);
    };
  fclose (fp);

  return 0;
}

int vlt_load_entries (const char *filename, const char *key)
{
  encrypted_entry encrypted;
  vlt_clear_entries ();
  size_t len = 0;

  auto fp = fopen (filename, "rb");
  fread (&len, sizeof (size_t), 1, fp);

  for (size_t i = 0; i < len; i++)
    {
      fread (&encrypted.ciphertext_len, sizeof (int), 1, fp);

      encrypted.ciphertext
          = malloc (sizeof (unsigned char) * encrypted.ciphertext_len);

      fread (encrypted.ciphertext, sizeof (unsigned char),
             encrypted.ciphertext_len, fp);
      fread (encrypted.iv, sizeof (unsigned char), IV_SIZE, fp);
      fread (encrypted.salt, sizeof (unsigned char), SALT_SIZE, fp);

      auto entry = vlt_decrypt_entry (&encrypted, key);
      free (encrypted.ciphertext);
      auto ptr = malloc (sizeof (entry));
      memcpy (ptr, &entry, sizeof (entry));
      vlt_add_entry (ptr);
    }
  fclose (fp);

  return len;
}
