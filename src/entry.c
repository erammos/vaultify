#include "entry.h"
#include "openssl/asn1err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vlt_entry *
vlt_entry_new ()
{
  vlt_entry *ptr = (vlt_entry *)calloc (1, sizeof (vlt_entry));

  if (ptr == NULL)
    {
      printf ("Memory allocation failed!\n");
      exit (0);
    }
  return ptr;
}
void
vlt_entry_ctr (vlt_entry *entry, const char *url, const char *username,
               const char *password)
{
  strcpy (entry->url, url);
  strcpy (entry->password, password);
  strcpy (entry->username, username);
}
void
vlt_entry_dtr (vlt_entry *entry)
{
  free (entry);
}
void
vlt_replace_from_str (vlt_entry *entry, char *str)
{

  char *temp = strdup (str);
  char *token = nullptr;
  if ((token = strtok (temp, "#")))
    {
      strcpy (entry->url, token);
    }
  if ((token = strtok (NULL, "#")))
    {
      strcpy (entry->username, token);
    }

  if ((token = strtok (NULL, "#")))
    {
      strcpy (entry->password, token);
    }
  free (temp);
}

char *
vlt_stringfy_entry (vlt_entry *entry)
{
  size_t url_sz = strlen (entry->url);
  size_t user_sz = strlen (entry->username);
  size_t pass_sz = strlen (entry->password);
  size_t size = url_sz + user_sz + pass_sz + 3;
  char *dst = (char *)calloc (size, sizeof (char));

  if (dst == NULL)
    {
      printf ("Memory allocation failed!\n");
      exit (0);
    }

  sprintf (dst, "%s#%s#%s", entry->url, entry->username, entry->password);
  return dst;
}
