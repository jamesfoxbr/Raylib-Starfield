#include "Space.h"
#include "Window.h"
#include "Controls.h"	
#include "SceneManager.h"
#include "Title.h"
#include "Globals.h"
#include "StarSystem.h"

// --------------------------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// --------------------------------------------------------------------------------------------
void windowSize();

// --------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
// --------------------------------------------------------------------------------------------

bool exitGame_g = false;                        // Exit game flag
LoadedScene loadedScene = TITLE;                // Current loaded scene

SceneManager sceneManager;                      // SceneManager instance
SceneManager& sceneManager_ref = sceneManager;  // SceneManager reference

Window window;                                  // Window instance
Camera& camera_ref = window.camera;             // Camera reference

Controls control;                               // Controls instance
Controls& control_ref = control;                // Controls reference

// --------------------------------------------------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------------------------------------------------
int main() 
{
	sceneManager.ChangeScene(new Title());

    // Main game loop
    while (!exitGame_g) 
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) exitGame_g = true;

		windowSize();

        // --------------------------------------------------------------------------------------------
		// UPDATE - INPUT
		// --------------------------------------------------------------------------------------------
		control.Update();

		// --------------------------------------------------------------------------------------------
		// UPDATE - SCENE
		// --------------------------------------------------------------------------------------------
        sceneManager.currentScene->Update();

        // --------------------------------------------------------------------------------------------
		// DRAW - SCENE 
		// --------------------------------------------------------------------------------------------

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

			
            
            BeginMode3D(window.camera);
            {
				// Draw the 3D scene
                sceneManager.currentScene->Draw3D();
            }
            EndMode3D();
            
            // Start 2D mode in front of the 3D image
            sceneManager.currentScene->Draw2D();
        }
        EndDrawing(); 
    }

    return 0;
}

// --------------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
// --------------------------------------------------------------------------------------------

// This function will check if the window has been resized and adjust the screen size accordingly
void windowSize()
{
    if (IsWindowResized() && !IsWindowFullscreen())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }
    // check for alt + enter
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
        // see what display we are on right now
        int display = GetCurrentMonitor();


        if (IsWindowFullscreen())
        {
            // if we are full screen, then go back to the windowed size
            SetWindowSize(screenWidth, screenHeight);
        }
        else
        {
            // if we are not full screen, set the window size to match the monitor we are on
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }

        // toggle the state
        ToggleFullscreen();
    }
}
