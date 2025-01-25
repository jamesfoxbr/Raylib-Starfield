#include "Starfield.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"

int main() {

    Window window;

    DisableCursor();   

    Starfield starfield(50000, 50);
    Controls control;

    // Main game loop
    while (!WindowShouldClose()) 
    {
        control.Move();
        UpdateCameraPro(&window.camera, control.cameraPosition, control.cameraRotation, CAMERA_CUSTOM);

        BeginDrawing(); 

            ClearBackground(BLACK);

        BeginMode3D(window.camera);

            starfield.DrawStars(window.camera);

        EndMode3D();

            DrawCoordinates(window.camera);
            targetCursor();

        EndDrawing(); 
    }
    return 0;
}