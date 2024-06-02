#include "entries.h"
#include "entry.h"
#include "stdlib.h"
#include "string.h"
#include "subprojects/unity/src/unity.h"
#include "unity.h"
#include <unistd.h>
/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp()
{
  vlt_clear_entries ();
}
void tearDown()
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
  size_t i = 1;
  LOOP (e, get_entries ())
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

  auto entries = get_entries ();
  TEST_ASSERT_EQUAL_CHAR_ARRAY (entries[0]->url, "url3", 4);
}

static bool cmp_url(vlt_entry * e1, vlt_entry * e2)
{
  return strcmp(e1->url,e2->url) == 0;
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
  auto e = vlt_find_entry_by(other3, &cmp_url);

  TEST_ASSERT_EQUAL_CHAR_ARRAY((*e)->url,"url3",4);

}
