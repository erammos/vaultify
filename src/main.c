/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "entry.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "vaultify.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void ShowClicked(char* list[],int index, char * text);
static void EditClicked();
static bool WindowBoxShowPasswordActive = false;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{


    auto entry1 = vlt_entry_new();
    auto entry2 = vlt_entry_new();
    auto entry3 = vlt_entry_new();
    vlt_entry_ctr(entry1,"www.google.com","gonzales","mypassword1");
    vlt_entry_ctr(entry2,"www.microsoft.com","anna","home123");
    vlt_entry_ctr(entry3,"www.exmaple.com","kostas","password1234");
    vlt_add_entry(entry1);
    vlt_add_entry(entry2);
    vlt_add_entry(entry3);

   
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Vector2 listAnchor = { 280, 208 };
    Vector2 ShowPasswordAnchor = { 400, 190 };
    
    int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
    bool TextBox004EditMode = false;
    char TextBoxUserName[MAX_USERNAME] = "username";
    bool TextBox005EditMode = false;
    char TextBoxPassword[MAX_PASS] = "password";
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------
       char ** list = nullptr;
       size_t list_len = vlt_get_list_by_url(&list);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

           int focus;
            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            GuiListViewEx((Rectangle){ listAnchor.x + -48, listAnchor.y + -88, 104, 192 }, list,list_len, &ListView000ScrollIndex, &ListView000Active,&focus);
            if (GuiButton((Rectangle){ listAnchor.x + 64, listAnchor.y + -88, 88, 24 }, "Show")) ShowClicked(list,ListView000Active,TextBoxPassword); 
            if (GuiButton((Rectangle){ listAnchor.x + 64, listAnchor.y + -48, 88, 24 }, "Edit")) EditClicked(); 

            if (WindowBoxShowPasswordActive)
            {
                WindowBoxShowPasswordActive = !GuiWindowBox((Rectangle){ ShowPasswordAnchor.x + -128, ShowPasswordAnchor.y + -64, 256, 136 }, "SAMPLE TEXT");
                if (GuiTextBox((Rectangle){ ShowPasswordAnchor.x + -56, ShowPasswordAnchor.y + 16, 120, 24 }, TextBoxPassword, 128, TextBox005EditMode)) TextBox005EditMode = !TextBox005EditMode;
            }
            //----------------------------------------------------------------------------------

        DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void ShowClicked(char* list[],int index, char * text)
{
  WindowBoxShowPasswordActive=true;

  auto entry = vlt_get_entry_by_url(list[index]);
  strcpy(text,entry->password);

    // TODO: Implement control logic
}
static void EditClicked()
{
    // TODO: Implement control logic
}

