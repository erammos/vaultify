#include "stdlib.h"
#include "string.h"
#include "unity.h"
#include "vaultify.h"

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
test_encryption_entry ()
{
  const char *password = "randompassword";
  vlt_entry_ctr (e, "home", "user", "password");
  auto encrypted = vlt_encrypt_entry (e, password);
  auto decr = vlt_decrypt_entry (&encrypted, password);

  TEST_ASSERT_EQUAL_CHAR_ARRAY ("home", decr.url, strlen ("home"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("user", decr.username, strlen ("user"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY ("password", decr.password,
                                strlen ("password"));
}