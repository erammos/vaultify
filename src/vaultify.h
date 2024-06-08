#ifndef _VAULTIFY_H
#define _VAULTIFY_H
#define _VLT_H_INSIDE
#include "encryption.h"
#include "entry.h"
#include "entries.h"
#define MAX_PASS 256

typedef struct
{
  bool is_logged_in;
  const char master_password[MAX_PASS];

} vlt_user;

typedef struct
{
  unsigned char *ciphertext;
  int ciphertext_len;
  unsigned char salt[SALT_SIZE];
  unsigned char iv[IV_SIZE];
} encrypted_entry;

encrypted_entry vlt_encrypt_entry (vlt_entry *entry, const char *key);
vlt_entry vlt_decrypt_entry (encrypted_entry *entry, const unsigned char *key);
bool vlt_login (vlt_user *user, const char *password);
size_t vlt_get_list_by_url (const char **list[]);
vlt_entry * vlt_get_entry_by_url (char url[]);
#undef _VLT_H_INSIDE
#endif
