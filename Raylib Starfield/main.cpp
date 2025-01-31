#include "Space.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"	
#include "Gui.h"

int main() {
    Window window;
    Controls control;
    Space space(window.camera);
    Gui gui;

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCameraPro(&window.camera, control.GetCameraPostion(), control.GetCameraRotation(), 0.0f);
        control.Update();

        BeginDrawing(); 
            ClearBackground(gui.GetClearColor());

            // 3D stuff go inside this area
            BeginMode3D(window.camera); 

                space.Update();
                space.Draw3D();

            // end of the 3d drawing area
            EndMode3D();
            // 2D stuff fixed to the screen space go in this area
            
                space.Draw2D();
                DrawCoordinates(window.camera);
                //targetCursor();
			    DrawDebugText("FPS: " + std::to_string(GetFPS()), 10, 30, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);

                gui.DrawInterface();

        EndDrawing(); 
    }
    return 0;
}