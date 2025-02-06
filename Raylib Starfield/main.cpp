#include "Space.h"
#include "Window.h"
#include "Controls.h"	


int main() 
{
    Window window;
    Controls control(window.camera);
    Space space(window.camera);

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

        UpdateCameraPro(&window.camera, control.GetCameraPostion(), control.GetCameraRotation(), 0.0f);
        control.Update();

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

            space.Update();
            
            BeginMode3D(window.camera);
            {
                space.Draw3D();
            }
            EndMode3D();
            
            // Start 2D mode in front of the 3D image
            space.Draw2D();

            //DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
            //DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);
        }
        EndDrawing(); 
    }
    return 0;
}


