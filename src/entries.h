#ifndef _ENTRIES_H
#define _ENTRIES_H
#if !defined(_VLT_H_INSIDE) && !defined(VLT_COMPILATION)
#error "Only <vaultify.h> can be included directly."
#endif
#include <entry.h>
#include <stddef.h>

#define MAX_ENTRIES 1024
#define LOOP(VAR, ARRAY) \
        for (typeof(*ARRAY) VAR, *_arr = ARRAY; (VAR = *_arr) != nullptr; ++_arr)
#define LOOP_PTR(VAR, ARRAY, PTR) \
        for (typeof(*ARRAY) VAR, *PTR = ARRAY; (VAR = *PTR) != nullptr; ++PTR)

typedef bool (*cmp_entry)(void *, void *);

void vlt_add_entry(vlt_entry * entry);
int vlt_remove_entry(vlt_entry * entry);
vlt_entry ** vlt_find_entry_by(vlt_entry * entry,cmp_entry);
size_t get_entries (vlt_entry ** out[]);
void vlt_clear_entries();

#endif