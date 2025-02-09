#include "Utils.h"


int diceRoller(int minimun, int maximun)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(minimun, maximun);

    return dist(mt);
}

double distance(const Vector3& p1, const Vector3& p2)
{
    const double d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2) * 1.0);
    return d;
}

void DrawCoordinates(const Camera& camera)
{
    const std::string positionX = "X: " + std::to_string(int(camera.position.x));
    const std::string positionY = " / Y: " + std::to_string(int(camera.position.y));
    const std::string positionZ = " / Z: " + std::to_string(int(camera.position.z));

    const std::string str = positionX + positionY + positionZ;  // Create the string first

    const char* cstr = str.c_str(); // Then get a const char* pointer
    DrawText(cstr, 10, 10, 20, RAYWHITE);
}

void targetCursor()
{
    // Draw a simple crosshair in the center
    Vector2 center = {static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2)};
    int size = 20;

    // Draw horizontal and vertical lines to form the target cursor
    DrawLine((int)center.x - size, (int)center.y, (int)center.x + size, (int)center.y, RAYWHITE);  // Horizontal line
    DrawLine((int)center.x, (int)center.y - size, (int)center.x, (int)center.y + size, RAYWHITE);  // Vertical line
}

void DrawDebugText(const std::string& text, int x, int y, int fontSize, Color color)
{
	const char* cstr = text.c_str(); // Then get a const char* pointer
	DrawText(cstr, x, y, fontSize, color);
}
