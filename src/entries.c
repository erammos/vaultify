
#include "entries.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static vlt_entry *entries[MAX_ENTRIES + 1] = { 0 };
static size_t num_entries = { 0 };
void
vlt_add_entry (vlt_entry *entry)
{
  if (num_entries >= MAX_ENTRIES)
    {
      fprintf (stderr, "Exceed max entries");
      exit (1);
    }

  entries[num_entries] = entry;
  num_entries++;
}
void
vlt_clear_entries ()
{

  memset (entries, 0, sizeof (vlt_entry *) * (MAX_ENTRIES + 1));
  num_entries = 0;
}
static bool
cmp_equal (void *entry, void *other)
{
  return entry == other;
}
int
vlt_remove_entry (vlt_entry *entry)
{
  cmp_entry fn = &cmp_equal;
  auto p = vlt_find_entry_by (entry, fn);
  if (*p != nullptr)
    {

      *p = entries[--num_entries];
      return 1;
    }

  return 0;
}
vlt_entry **
vlt_find_entry_by (vlt_entry *entry, cmp_entry compare)
{
  vlt_entry **p = nullptr;
  LOOP_PTR (e, entries, ptr)
  {
    if (compare (e, entry))
      {
        p = ptr;
        return p;
      }
  }
  return nullptr;
}

size_t get_entries (vlt_entry ** out[])
{
  
  *out = entries;
  return num_entries;
}
