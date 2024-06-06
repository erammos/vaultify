#include "entry.h"
#include "raylib.h"

#include "gui_common.h"
#include "gui_dialog_show_password.h"
#include "gui_list_urls.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "vaultify.h"

static GuiPasswordDialogState password_dialog;

static void
OnClickViewBtn (GuiListUrlsState *state, int index)
{
  if (index < 0)
    return;
  auto entry = vlt_get_entry_by_url (state->items[index]);
  UpdateGuiPasswordDialog (&password_dialog, entry->username, entry->password);
  ShowGuiPasswordDialog (&password_dialog);
}
static void
OnClickEditBtn (GuiListUrlsState *state, int index)
{
  if (index < 0)
    return;
}
static void
OnClickAddBtn (GuiListUrlsState *state, int index)
{
  if (index < 0)
    return;
}
static void
OnClickDelBtn (GuiListUrlsState *state, int index)
{
  if (index < 0)
    return;
}

int
main ()
{

  auto entry1 = vlt_entry_new ();
  auto entry2 = vlt_entry_new ();
  auto entry3 = vlt_entry_new ();
  vlt_entry_ctr (entry1, "www.google.com", "gonzales", "mypassword1");
  vlt_entry_ctr (entry2, "www.microsoft.com", "anna", "home123");
  vlt_entry_ctr (entry3, "www.exmaple.com", "kostas", "password1234");
  vlt_add_entry (entry1);
  vlt_add_entry (entry2);
  vlt_add_entry (entry3);

  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Demo");

  auto list_view = InitGuiListUrls (&OnClickViewBtn, &OnClickEditBtn,
                                    &OnClickAddBtn, &OnClickDelBtn);
  password_dialog = InitGuiPasswordDialog ();

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
      DrawFPS (10, 10);
      EndDrawing ();
    }

  CloseWindow (); // Close window and OpenGL context

  return 0;
}
