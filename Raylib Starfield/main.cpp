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

        // end of the 3d drawing area
        EndMode3D();

        // 2D stuff fized to the screen space go in this area
            DrawCoordinates(window.camera);
            targetCursor();

        EndDrawing(); 
    }
    return 0;
}