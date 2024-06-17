#include "entry.h"
#include "raylib.h"

#include "gui_common.h"
#include "gui_dialog_show_password.h"
#include "gui_edit_url.h"
#include "gui_list_urls.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "vaultify.h"

static GuiPasswordDialogState password_dialog;
static GuiEditUrlState edit_url_dialog;
static GuiListUrlsState list_view;

static void
OnClickViewBtn (GuiListUrlsState *state, int index)
{
  if (index < 0 || vlt_get_entries_size () <= 0
      || index >= vlt_get_entries_size ())
    return;
  auto entry = vlt_get_entry_by_url (state->items[index]);
  UpdateGuiPasswordDialog (&password_dialog, entry->username, entry->password);
  ShowGuiPasswordDialog (&password_dialog);
  list_view.is_visible = false;
}
static void
OnClickEditBtn (GuiListUrlsState *state, int index)
{
  if (index < 0 || vlt_get_entries_size () <= 0
      || index >= vlt_get_entries_size ())
    return;
}
static void
OnClickAddBtn (GuiListUrlsState *state, int index)
{
  ShowEditUrl (&edit_url_dialog);
  list_view.is_visible = false;
}
static void
OnClickDelBtn (GuiListUrlsState *state, int index)
{
  if (index < 0 || vlt_get_entries_size () <= 0
      || index >= vlt_get_entries_size ())
    return;
  auto entry = vlt_get_entry_by_url (state->items[index]);
  vlt_remove_entry (entry);
}

static void
saveOnAddBtn (GuiEditUrlState *state)
{
  auto entry = vlt_entry_new ();
  vlt_entry_ctr (entry, state->url_text, state->username_text,
                 state->password_text);
  vlt_add_entry (entry);
  vlt_save_entries ("saved.data", "mypassword");
}

static void
OnCloseDialog ()
{
  list_view.is_visible = true;
}
int
main ()
{

  vlt_load_entries ("saved.data", "mypassword");
  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Demo");
  list_view = InitGuiListUrls (&OnClickViewBtn, &OnClickEditBtn,
                               &OnClickAddBtn, &OnClickDelBtn);
  password_dialog = InitGuiPasswordDialog (&OnCloseDialog);
  edit_url_dialog = InitGuiEditUrl (&saveOnAddBtn, &OnCloseDialog);

  SetTargetFPS (60);

  // Main game loop
  while (!WindowShouldClose ()) // Detect window close button or ESC key
    {

      const char **list = nullptr;
      size_t list_len = vlt_get_list_by_url (&list);
      UpdateList (&list_view, list, list_len);
      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing ();

      ClearBackground (GetColor (GuiGetStyle (DEFAULT, BACKGROUND_COLOR)));

      DrawGuiListUrls (&list_view);
      DrawGuiPasswordDialog (&password_dialog);
      DrawGuiEditUrl (&edit_url_dialog);
      DrawFPS (10, 10);
      EndDrawing ();
    }

  CloseWindow (); // Close window and OpenGL context

  return 0;
}
