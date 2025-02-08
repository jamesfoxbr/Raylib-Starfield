#include "Space.h"
#include "Window.h"
#include "Controls.h"	
#include "SceneManager.h"
#include "Title.h"

enum currentScene
{
    TITLE,
    SPACE
};

int main() 
{
    Window window;    

    // Start with the title scene
    SceneManager::ChangeScene(new Title());

    // Main game loop
    while (!WindowShouldClose()) 
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

        // --------------------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER))
        {
            SceneManager::ChangeScene(new Space(window.camera));
        }
        if (IsKeyPressed(KEY_T))
        {
            SceneManager::ChangeScene(new Title());
        }


        // --------------------------------------------------------------------------------------------

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

            SceneManager::currentScene->Update();
            
            BeginMode3D(window.camera);
            {
                SceneManager::currentScene->Draw3D();
            }
            EndMode3D();
            
            // Start 2D mode in front of the 3D image
            SceneManager::currentScene->Draw2D();

            //DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
            //DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);
        }
        EndDrawing(); 
    }

    // Cleanup before exit
    if (SceneManager::currentScene) {
        SceneManager::currentScene->Unload();
        delete SceneManager::currentScene;
    }

    return 0;
}


