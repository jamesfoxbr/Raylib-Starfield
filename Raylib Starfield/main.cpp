#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>
#include "Starfield.h"

int main() {

    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "FPS-like 3D Star Field");
    SetTargetFPS(60);

    // Draw a simple crosshair in the center
    Vector2 center = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)};
    int size = 20;
    Color cursorColor = RAYWHITE;

    // Camera setup
    Camera3D camera = {0};
    camera.position = {0.0f, 1.75f, 10.0f};  // Camera position (eye level about 1.75m)
    camera.target = {0.0f, 1.75f, 0.0f};     // Camera target (look at the origin)
    camera.up = {0.0f, 1.0f, 0.0f};          // Camera up direction (Y-axis)
    camera.fovy = 45.0f;                     // Field of view (in degrees)
    camera.projection = CAMERA_PERSPECTIVE;  // Set perspective projection

    // Disable the mouse cursor and set it to the center of the screen
    //HideCursor();
    DisableCursor();   

    Starfield starfield(5000, 50);

    // Main game loop
    while (!WindowShouldClose()) {

        // Camera movement using WASD (with E and Q for vertical movement)
        UpdateCamera(&camera, CAMERA_FREE);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        starfield.DrawStars(camera);

        EndMode3D();

        std::string positionX = "X: " + std::to_string(camera.position.x);
        std::string positionY = " / Y: " + std::to_string(camera.position.y);
        std::string positionZ = " / Z: " + std::to_string(camera.position.z);

        std::string str = positionX + positionY + positionZ;  // Create the string first

        const char* cstr = str.c_str();        // Then get a const char* pointer
        DrawText(cstr, 10, 10, 20, RAYWHITE);

        // Draw horizontal and vertical lines to form the target cursor
        DrawLine((int)center.x - size, (int)center.y, (int)center.x + size, (int)center.y, cursorColor);  // Horizontal line
        DrawLine((int)center.x, (int)center.y - size, (int)center.x, (int)center.y + size, cursorColor);  // Vertical line

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); 

    return 0;
}
