#ifndef _ENTRY_H
#define _ENTRY_H
#define _VLT_H_INSIDE
#define MAX_URL 2000
#define MAX_PASS 256
#define MAX_USERNAME 64
#define MAX_INFO 256
typedef struct
{
  char url[MAX_URL];
  char username[MAX_USERNAME];
  char password[MAX_PASS];
  char info[MAX_INFO];

} vlt_entry;

vlt_entry *vlt_entry_new ();
void vlt_entry_ctr (vlt_entry *entry, const char *url, const char *username,
                    const char *password);
void vlt_entry_dtr (vlt_entry *entry);
char *vlt_stringfy_entry (vlt_entry *entry);
void vlt_replace_from_str (vlt_entry *entry, char *str);

#endif
