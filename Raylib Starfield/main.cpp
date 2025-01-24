#include "Starfield.h"
#include "Globals.h"
#include "Window.h"

int main() {

    Window window;

    DisableCursor();   

    Starfield starfield(5000, 50);

    // Main game loop
    while (!WindowShouldClose()) {

        UpdateCamera(&window.camera, CAMERA_FREE);

        BeginDrawing(); 

            ClearBackground(BLACK);

        BeginMode3D(window.camera);

            starfield.DrawStars(window.camera);

        EndMode3D();

            DrawCoordinates(window.camera);
            targetCursor();

        EndDrawing(); 
    }

    // De-Initialization
    CloseWindow(); 

    return 0;
}