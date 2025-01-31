#include "Space.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"

int main() {
    Window window;
    Controls control;
    Space space(window.camera);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCameraPro(&window.camera, control.GetCameraPostion(), control.GetCameraRotation(), 0.0f);
        control.Update();

        BeginDrawing(); 
            ClearBackground(BLACK);

            // 3D stuff go inside this area
            BeginMode3D(window.camera); 

                space.Update();
                space.Draw3D();

            // end of the 3d drawing area
            EndMode3D();

            space.Draw2D();

            // 2D stuff fized to the screen space go in this area
                DrawCoordinates(window.camera);
                targetCursor();
			    DrawDebugText("FPS: " + std::to_string(GetFPS()), 10, 30, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);

        EndDrawing(); 
    }
    return 0;
}