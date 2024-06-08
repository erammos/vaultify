
#include "gui_common.h"
#include "raylib.h"

#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h> // Required for: strcpy()

#ifndef GUI_EDIT_URL_H
#define GUI_EDIT_URL_H
typedef struct GuiEditUrlState GuiEditUrlState;
typedef void (*OnClickSaveBtn) (GuiEditUrlState *);
static void Clear (GuiEditUrlState *state);
struct GuiEditUrlState
{
  Vector2 anchor;

  bool dialog_active;
  bool url_edit;
  char url_text[128];
  bool username_edit;
  char username_text[128];
  bool password_edit;
  char password_text[128];
  bool info_edit;
  char info_text[128];
  OnClickSaveBtn saveBtnPressed;
};

GuiEditUrlState InitGuiEditUrl (OnClickSaveBtn save_cb);
void DrawGuiEditUrl (GuiEditUrlState *state);

#endif // GUI_EDIT_URL_H

#include "raygui.h"

GuiEditUrlState
InitGuiEditUrl (OnClickSaveBtn save_cb)
{
  GuiEditUrlState state = { 0 };

  state.anchor
      = (Vector2){ SCREEN_WIDTH / 2 - 288 / 2, SCREEN_HEIGHT / 2 - 248 / 2 };

  state.dialog_active = false;
  state.url_edit = false;
  state.username_edit = false;
  state.password_edit = false;
  state.info_edit = false;
  state.saveBtnPressed = save_cb;
  Clear (&state);

  return state;
}
static void
Clear (GuiEditUrlState *state)
{
  strcpy (state->url_text, "");
  strcpy (state->username_text, "");
  strcpy (state->password_text, "");
  strcpy (state->info_text, "");
}
void
ShowEditUrl (GuiEditUrlState *state)
{
  state->dialog_active = true;
  Clear (state);
}
void
CloseEditUrl (GuiEditUrlState *state)
{
  state->dialog_active = false;
  Clear (state);
}

void
DrawGuiEditUrl (GuiEditUrlState *state)
{
  if (state->dialog_active)
    {
      GuiSetStyle (TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

      state->dialog_active = !GuiWindowBox (
          (Rectangle){ state->anchor.x + 0, state->anchor.y + 0, 288, 248 },
          "Add Url");
      if (GuiTextBox ((Rectangle){ state->anchor.x + 112, state->anchor.y + 56,
                                   120, 24 },
                      state->url_text, 128, state->url_edit))
        state->url_edit = !state->url_edit;
      if (GuiTextBox ((Rectangle){ state->anchor.x + 112, state->anchor.y + 88,
                                   120, 24 },
                      state->username_text, 128, state->username_edit))
        state->username_edit = !state->username_edit;
      if (GuiTextBox ((Rectangle){ state->anchor.x + 112,
                                   state->anchor.y + 120, 120, 24 },
                      state->password_text, 128, state->password_edit))
        state->password_edit = !state->password_edit;
      if (GuiTextBox ((Rectangle){ state->anchor.x + 112,
                                   state->anchor.y + 152, 120, 40 },
                      state->info_text, 128, state->info_edit))
        state->info_edit = !state->info_edit;
      if (strlen (state->url_text) < 2 || strlen (state->username_text) < 2
          || strlen (state->password_text) < 2)
        GuiSetState (STATE_DISABLED);
      if (GuiButton ((Rectangle){ state->anchor.x + 80, state->anchor.y + 208,
                                  120, 24 },
                     "Save"))
        {

          state->saveBtnPressed (state);
          CloseEditUrl (state);
        }
      GuiSetState (STATE_NORMAL);
      GuiLabel (
          (Rectangle){ state->anchor.x + 16, state->anchor.y + 56, 88, 24 },
          "Url");
      GuiLabel (
          (Rectangle){ state->anchor.x + 16, state->anchor.y + 88, 88, 24 },
          "Username");
      GuiLabel (
          (Rectangle){ state->anchor.x + 16, state->anchor.y + 120, 88, 24 },
          "Password");
      GuiLabel (
          (Rectangle){ state->anchor.x + 16, state->anchor.y + 152, 88, 24 },
          "Info");
    }
}
