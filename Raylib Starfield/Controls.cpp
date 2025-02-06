#include "Controls.h"


Controls::Controls(Camera& camera)
	: camera(camera)
{
	cameraPosition = {0.0f, 0.0f, 0.0f};
	CurrentMousePosition = GetMousePosition();
	LastMousePosition = CurrentMousePosition;
}

Controls::~Controls()
{
}

void Controls::Update()
{
	cameraPosition = {0.0f, 0.0f, 0.0f};
	cameraRotation = {0.0f, 0.0f, 0.0f};
	Move();
	MouseLook();
}

void Controls::Move()
{
	/*auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return;
	}*/

	// Set movement speed
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		speed = 0.2f;
	}
	else
	{
		speed = 0.05f;
	}

	// Check buttons pressed
	if (IsKeyDown(KEY_W))
	{
		Accelleration.x += speed;
	}
	if (IsKeyDown(KEY_S))
	{
		Accelleration.x += -speed;
	}
	if (IsKeyDown(KEY_D))
	{
		Accelleration.y += speed;
	}
	if (IsKeyDown(KEY_A))
	{
		Accelleration.y += -speed;
	}
	if (IsKeyDown(KEY_SPACE))
	{
		Accelleration.z += speed;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		Accelleration.z += -speed;
	}
	
	// Reduce acceleration until it reaches zero
	float deceleration = 0.1f;
	if (Accelleration.x > 0 && !IsKeyDown(KEY_W))
	{
		Accelleration.x -= deceleration;
		if (Accelleration.x < 0) Accelleration.x = 0;
	}
	else if (Accelleration.x < 0 && !IsKeyDown(KEY_S))
	{
		Accelleration.x += deceleration;
		if (Accelleration.x > 0) Accelleration.x = 0;
	}

	if (Accelleration.y > 0 && !IsKeyDown(KEY_D))
	{
		Accelleration.y -= deceleration;
		if (Accelleration.y < 0) Accelleration.y = 0;
	}
	else if (Accelleration.y < 0 && !IsKeyDown(KEY_A))
	{
		Accelleration.y += deceleration;
		if (Accelleration.y > 0) Accelleration.y = 0;
	}

	if (Accelleration.z > 0 && !IsKeyDown(KEY_SPACE))
	{
		Accelleration.z -= deceleration;
		if (Accelleration.z < 0) Accelleration.z = 0;
	}
	else if (Accelleration.z < 0 && !IsKeyDown(KEY_LEFT_CONTROL))
	{
		Accelleration.z += deceleration;
		if (Accelleration.z > 0) Accelleration.z = 0;
	}
	

	cameraPosition = Accelleration;
}

void Controls::MouseLook()
{
	/*auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return;
	}*/

	CurrentMousePosition = GetMousePosition();
	Vector2 storeMousePosition;
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		if (cursorEnable)
		{
			storeMousePosition = GetMousePosition();
			DisableCursor();
			SetMousePosition((int)storeMousePosition.x, (int)storeMousePosition.y);
			CurrentMousePosition = GetMousePosition();
			cursorEnable = false;
		}

		if (LastMousePosition.x != CurrentMousePosition.x)
		{
			cameraRotation.x = (CurrentMousePosition.x - LastMousePosition.x) * mouseSensibility;
		}
		if (LastMousePosition.y != CurrentMousePosition.y)
		{
			cameraRotation.y = (CurrentMousePosition.y - LastMousePosition.y) * mouseSensibility;
		}
	}
	else
	{
		if (!cursorEnable)
		{
			EnableCursor();
			cursorEnable = true;
		}
	}
	LastMousePosition = CurrentMousePosition;
}

Vector3 Controls::GetCameraPostion()
{
	return cameraPosition;
}

Vector3 Controls::GetCameraRotation()
{
	return cameraRotation;
}
