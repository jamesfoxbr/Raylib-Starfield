#include "Controls.h"

Controls::Controls()
{
}

Controls::~Controls()
{
}

void Controls::Move()
{
	cameraPosition = {0.0f, 0.0f, 0.0f};

	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		speed += 0.2f;
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
}
