#include "Controls.h"
#include <iostream>
Controls::Controls()
{
	cameraPosition = {0.0f, 0.0f, 0.0f};
	CurrentMousePosition = GetMousePosition();
	LastMousePosition = CurrentMousePosition;
}

Controls::~Controls()
{
}

void Controls::Move()
{
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		speed = 1.0f;
	}
	else
	{
		speed = 0.2f;
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
	CurrentMousePosition = GetMousePosition();
	

	if (LastMousePosition.x != CurrentMousePosition.x)
	{
		cameraRotation.x = CurrentMousePosition.x - LastMousePosition.x;
	}
	if (LastMousePosition.y != CurrentMousePosition.y)
	{
		cameraRotation.y = CurrentMousePosition.y - LastMousePosition.y;
	}

	LastMousePosition = CurrentMousePosition;
	
}
