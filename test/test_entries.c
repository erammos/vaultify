#include "entries.h"
#include "entry.h"
#include "stdlib.h"
#include "string.h"
#include "unity.h"
#include "vaultify.h"
#include <unistd.h>
/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void
setUp ()
{
  vlt_clear_entries ();
}
void
tearDown ()
{
}
void
test_insert_entries ()
{
  auto e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url1", "234", "test");
  auto e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url2", "234", "test");
  auto e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url3", "234", "test");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);
  vlt_entry **array;
  int i = 1;
  get_entries (&array);
  LOOP (e, array)
  {

    char test[5] = { 'u', 'r', 'l', [4] = '\0' };
    test[3] = i + '0';
    TEST_ASSERT_EQUAL_CHAR_ARRAY (e->url, test, strlen (test));
    i++;
  }
}
void
test_remove_entries1 ()
{
  auto e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url1", "234", "test");
  auto e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url2", "234", "test");
  auto e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url3", "234", "test");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);
  vlt_remove_entry (e2);
  vlt_remove_entry (e1);
  vlt_entry **entries;
  get_entries (&entries);
  TEST_ASSERT_EQUAL_CHAR_ARRAY (entries[0]->url, "url3", 4);
}

static bool
cmp_url (void *e1, void *e2)
{
  return strcmp (((vlt_entry *)e1)->url, ((vlt_entry *)e2)->url) == 0;
}
void
test_find_entries ()
{
  vlt_clear_entries ();
  auto e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url1", "234", "test");
  auto e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url2", "234", "test");
  auto e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url3", "234", "test");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);

  auto other3 = vlt_entry_new ();
  vlt_entry_ctr (other3, "url3", "234", "test");
  auto e = vlt_find_entry_by (other3, &cmp_url);

  TEST_ASSERT_EQUAL_CHAR_ARRAY ((*e)->url, "url3", 4);
}

void
test_list_by_url ()
{
  vlt_clear_entries ();
  auto e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url1", "234", "test");
  auto e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url2", "234", "test");
  auto e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url3", "234", "test");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);

  char **list = nullptr;
  vlt_get_list_by_url (&list);
  TEST_ASSERT_EQUAL_CHAR_ARRAY (list[1], "url2", 4);
}

void
test_vlt_save ()
{

  auto e = vlt_entry_new ();
  vlt_entry_ctr (e, "home", "user", "password");
  vlt_add_entry (e);

  auto encrypted = vlt_encrypt_entry (e, "mypassword");

  vlt_entry **entries;
  size_t len = get_entries (&entries);

  auto fp = fopen ("test.dat", "wb+");
  fwrite (&len, sizeof (size_t), 1, fp);
  fwrite (&encrypted.ciphertext_len, sizeof (int), 1, fp);
  fwrite (encrypted.ciphertext, sizeof (unsigned char),
          encrypted.ciphertext_len, fp);
  fwrite (encrypted.iv, sizeof (unsigned char), IV_SIZE, fp);
  fwrite (encrypted.salt, sizeof (unsigned char), SALT_SIZE, fp);
  fflush (fp);
  fclose (fp);

  free (encrypted.ciphertext);
  encrypted.ciphertext = nullptr;
  encrypted.ciphertext_len = 0;
  memset (encrypted.iv, 0, IV_SIZE);
  memset (encrypted.salt, 0, SALT_SIZE);

  fp = fopen ("test.dat", "r");
  fread (&len, sizeof (size_t), 1, fp);
  fread (&encrypted.ciphertext_len, sizeof (int), 1, fp);

  encrypted.ciphertext
      = malloc (sizeof (unsigned char) * encrypted.ciphertext_len);

  fread (encrypted.ciphertext, sizeof (unsigned char),
         encrypted.ciphertext_len, fp);
  fread (encrypted.iv, sizeof (unsigned char), IV_SIZE, fp);
  fread (encrypted.salt, sizeof (unsigned char), SALT_SIZE, fp);
  fclose (fp);

  auto decrypted = vlt_decrypt_entry (&encrypted, "mypassword");
  free (encrypted.ciphertext);

  TEST_ASSERT_EQUAL_CHAR_ARRAY ("home", decrypted.url, strlen ("home"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("user", decrypted.username, strlen ("user"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("password", decrypted.password,
                                strlen ("password"));
}
void
test_vlt_save_all ()
{

  vlt_clear_entries ();
  auto e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url1", "user1", "password1");
  auto e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url2", "user2", "password2");
  auto e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url3", "user3", "password3");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);

  vlt_save_entries ("test2.data", "mypassword");

  vlt_clear_entries ();
  e1 = vlt_entry_new ();
  vlt_entry_ctr (e1, "url4", "xaxa", "password1");
  e2 = vlt_entry_new ();
  vlt_entry_ctr (e2, "url5", "xaxaxa", "password2");
  e3 = vlt_entry_new ();
  vlt_entry_ctr (e3, "url6", "xaxaxa", "password3");

  vlt_add_entry (e1);
  vlt_add_entry (e2);
  vlt_add_entry (e3);
  vlt_load_entries ("test2.data", "mypassword");
  vlt_entry **array;
  int i = 1;
  get_entries (&array);
  LOOP (e, array)
  {

    char test[10] = { 'u', 'r', 'l', [4] = '\0' };
    test[3] = i + '0';
    TEST_ASSERT_EQUAL_CHAR_ARRAY (e->url, test, strlen (test));
    i++;
  }
}
