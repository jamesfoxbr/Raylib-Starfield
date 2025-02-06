#include "Controls.h"


Controls::Controls()
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

	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		speed = 2.0f;
	}
	else
	{
		speed = 0.5f;
	}

	if (IsKeyDown(KEY_W))
	{
		cameraPosition.x = speed;

	}
	else if (IsKeyDown(KEY_S))
	{
		cameraPosition.x = -speed;
	}

	if (IsKeyDown(KEY_D))
	{
		cameraPosition.y = speed;
	}
	else if (IsKeyDown(KEY_A))
	{
		cameraPosition.y = -speed;
	}

	if (IsKeyDown(KEY_SPACE))
	{
		cameraPosition.z = speed;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		cameraPosition.z = -speed;
	}
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
