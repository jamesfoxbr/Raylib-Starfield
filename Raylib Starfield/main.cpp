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

        BeginMode3D(window.camera);

        space.Update();

        EndMode3D();

            DrawCoordinates(window.camera);
            targetCursor();

        EndDrawing(); 
    }
    return 0;
}