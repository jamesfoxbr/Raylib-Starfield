#include "Window.h"

Window::Window()
{
	// Initialization
	InitWindow(screenWidth, screenHeight, "FPS-like 3D Star Field");
	SetTargetFPS(60);

	// Camera setup
	camera.position = Vector3{0.0f, 0.0f, 10.0f};  // Camera position (eye level about 1.75m)
	camera.target = Vector3{0.0f, 0.0f, 0.0f};       // Camera target (look at the origin)
	camera.up = Vector3{0.0f, 1.0f, 0.0f};           // Camera up direction (Y-axis)
	camera.fovy = 45.0f;                             // Field of view (in degrees)
	camera.projection = CAMERA_PERSPECTIVE;          // Set perspective projection

	DisableCursor();
}

Window::~Window()
{
	// De-Initialization
	CloseWindow();
}
