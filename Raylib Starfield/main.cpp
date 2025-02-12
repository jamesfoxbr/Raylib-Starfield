#include "Space.h"
#include "Window.h"
#include "Controls.h"	
#include "SceneManager.h"
#include "Title.h"
#include "Globals.h"
#include "StarSystem.h"


// Function prototypes
void windowSize();

// Global variables
bool exitGame_g = false;
LoadedScene loadedScene = TITLE;

SceneManager sceneManager;
SceneManager& sceneManager_ref = sceneManager;

Window window;
Camera& camera_ref = window.camera;

int main() 
{
	sceneManager.ChangeScene(new Title());

    // Main game loop
    while (!exitGame_g) 
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) exitGame_g = true;

		windowSize();
		//menu(currentScene, window);

        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

            sceneManager.currentScene->Update();
            
            BeginMode3D(window.camera);
            {
                sceneManager.currentScene->Draw3D();
            }
            EndMode3D();
            
            // Start 2D mode in front of the 3D image
            sceneManager.currentScene->Draw2D();

            //DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
            //DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);
        }
        EndDrawing(); 
    }

    return 0;
}

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
