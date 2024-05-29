#include "vaultify.h"
#include <gtk/gtk.h>

int
main (int argc, char *argv[])
{

   vlt_entry e = {0};
  vlt_entry_ctr(&e, "home", "user", "password");
  const char * password = "xaxaxa";
   auto encrypted = vlt_encrypt_entry (&e, password);
   auto decr = vlt_decrypt_entry (&encrypted, password);
  

  return 0;
}