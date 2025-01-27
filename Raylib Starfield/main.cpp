#include "Space.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"

int main() {

    Window window;

    DisableCursor();   

    Controls control;

    Space space(window.camera);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        control.MouseLook();
        control.Move();
        UpdateCameraPro(&window.camera, control.cameraPosition, control.cameraRotation, CAMERA_CUSTOM);
        control.cameraPosition = {0.0f, 0.0f, 0.0f};
        control.cameraRotation = {0.0f, 0.0f, 0.0f};

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