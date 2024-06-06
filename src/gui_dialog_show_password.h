#include "entry.h"
#include "gui_common.h"
#include "raylib.h"
#include "vaultify.h"

#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>

#ifndef GUI_PASSWORDDIALOG_H
#define GUI_PASSWORDDIALOG_H

typedef struct
{
  Vector2 anchor;
  bool dialog_active;
  char user_name_text[MAX_USERNAME];
  char hidden_password[MAX_PASS];
  char password[MAX_PASS];

} GuiPasswordDialogState;

GuiPasswordDialogState InitGuiPasswordDialog (void);
void GuiPasswordDialog (GuiPasswordDialogState *state);

#endif // GUI_PASSWORDDIALOG_H

#include "raygui.h"

GuiPasswordDialogState
InitGuiPasswordDialog (void)
{
  GuiPasswordDialogState state = { 0 };

  state.anchor = (Vector2){ (float)SCREEN_WIDTH / 2 - 200.0 / 2,
                            (float)SCREEN_HEIGHT / 2 - 144.0 / 2 };

  state.dialog_active = false;
  strcpy (state.user_name_text, "");
  strcpy (state.hidden_password, "");

  return state;
}

void
ShowGuiPasswordDialog (GuiPasswordDialogState *state)
{
  state->dialog_active = true;
}
void
UpdateGuiPasswordDialog (GuiPasswordDialogState *state, const char *username,
                         const char *password)
{
  strcpy (state->user_name_text, username);
  strcpy (state->password, password);
  for (size_t i = 0; i < strlen (password); i++)
    {
      state->hidden_password[i] = '*';
    }
}
void
DrawGuiPasswordDialog (GuiPasswordDialogState *state)
{
  if (state->dialog_active)
    {
      state->dialog_active = !GuiWindowBox (
          (Rectangle){ state->anchor.x + 0, state->anchor.y + 0, 200, 200 },
          "Password View");
      GuiSetStyle (TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
      GuiTextBox (
          (Rectangle){ state->anchor.x + 32, state->anchor.y + 48, 120, 24 },
          state->user_name_text, 128, false);
      GuiTextBox (
          (Rectangle){ state->anchor.x + 32, state->anchor.y + 88, 120, 24 },
          state->hidden_password, 128, false);
      if (GuiButton ((Rectangle){ state->anchor.x + 160, state->anchor.y + 48,
                                  24, 24 },
                     "cpy"))
        SetClipboardText (state->user_name_text);
      if (GuiButton ((Rectangle){ state->anchor.x + 160, state->anchor.y + 88,
                                  24, 24 },
                     "cpy"))
        SetClipboardText (state->password);
    }
}
