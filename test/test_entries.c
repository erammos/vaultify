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
  vlt_entry * *array;
  int i = 1;
  get_entries(&array);
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
  vlt_entry * *entries;
  get_entries (&entries);
  TEST_ASSERT_EQUAL_CHAR_ARRAY (entries[0]->url, "url3", 4);
}

static bool cmp_url(void * e1, void * e2)
{
  return strcmp(((vlt_entry *)e1)->url,((vlt_entry *) e2)->url) == 0;
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

char ** list = nullptr;
vlt_get_list_by_url(&list);
TEST_ASSERT_EQUAL_CHAR_ARRAY(list[1], "url2",4);

}
