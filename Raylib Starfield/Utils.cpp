#include "Utils.h"

double distance(Vector3 p1, Vector3 p2)
{
    double d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2) * 1.0);
    return d;
}

void DrawCoordinates(Camera camera)
{
    std::string positionX = "X: " + std::to_string(camera.position.x);
    std::string positionY = " / Y: " + std::to_string(camera.position.y);
    std::string positionZ = " / Z: " + std::to_string(camera.position.z);

    std::string str = positionX + positionY + positionZ;  // Create the string first

    const char* cstr = str.c_str();        // Then get a const char* pointer
    DrawText(cstr, 10, 10, 20, RAYWHITE);
}

void targetCursor()
{
    // Draw a simple crosshair in the center
    Vector2 center = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)};
    int size = 20;
    Color cursorColor = RAYWHITE;

    // Draw horizontal and vertical lines to form the target cursor
    DrawLine((int)center.x - size, (int)center.y, (int)center.x + size, (int)center.y, cursorColor);  // Horizontal line
    DrawLine((int)center.x, (int)center.y - size, (int)center.x, (int)center.y + size, cursorColor);  // Vertical line
}
