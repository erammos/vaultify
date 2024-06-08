#include "raylib.h"

#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "gui_common.h"
#include <stddef.h>

#ifndef GUI_LIST_URLS_H
#define GUI_LIST_URLS_H
typedef struct GuiListUrlsState GuiListUrlsState;
typedef void (*OnClickBtn) (GuiListUrlsState *, int);
struct GuiListUrlsState
{
  Vector2 anchor;

  int scroll_index;
  int active_index;
  OnClickBtn view_cb;
  OnClickBtn edit_cb;
  OnClickBtn add_cb;
  OnClickBtn del_cb;
  const char **items;
  size_t itemLength;
};

GuiListUrlsState InitGuiListUrls (OnClickBtn viewCb, OnClickBtn editCb,
                                  OnClickBtn addCb, OnClickBtn delCb);
void DrawGuiListUrls (GuiListUrlsState *state);
void UpdateList (GuiListUrlsState *state, const char *text[], int length);

#endif

GuiListUrlsState
InitGuiListUrls (OnClickBtn view_cb, OnClickBtn edit_cb, OnClickBtn add_cb,
                 OnClickBtn del_cb)
{
  GuiListUrlsState state = { 0 };

  state.anchor = (Vector2){ (float)SCREEN_WIDTH / 2 - 192.0 / 2,
                            (float)SCREEN_HEIGHT / 2 - 136.0 / 2 };

  state.scroll_index = 0;
  state.active_index = 0;
  state.add_cb = add_cb;
  state.view_cb = view_cb;
  state.del_cb = del_cb;
  state.edit_cb = edit_cb;

  return state;
}

void
UpdateList (GuiListUrlsState *state, const char *text[], int length)
{
  state->items = text;
  state->itemLength = length;
}

void
DrawGuiListUrls (GuiListUrlsState *state)
{
  int focus;
  GuiListViewEx (
      (Rectangle){ state->anchor.x + 0, state->anchor.y + 24, 192, 136 },
      state->items, state->itemLength, &state->scroll_index,
      &state->active_index, &focus);
  if (GuiButton (
          (Rectangle){ state->anchor.x + 0, state->anchor.y + 0, 48, 24 },
          "VIEW"))
    state->view_cb (state, state->active_index);
  if (GuiButton (
          (Rectangle){ state->anchor.x + 48, state->anchor.y + 0, 48, 24 },
          "EDIT"))
    state->edit_cb (state, state->active_index);
  if (GuiButton (
          (Rectangle){ state->anchor.x + 96, state->anchor.y + 0, 48, 24 },
          "ADD"))
    state->add_cb (state, state->active_index);
  if (GuiButton (
          (Rectangle){ state->anchor.x + 144, state->anchor.y + 0, 48, 24 },
          "DEL"))
    state->del_cb (state, state->active_index);
}
