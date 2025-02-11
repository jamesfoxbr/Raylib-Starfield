#include "StarSystem.h"

StarSystem::StarSystem(Camera& camera)
	: camera(camera)
{
	control = new Controls(camera);
}

StarSystem::~StarSystem()
{
}

void StarSystem::Init()
{
}

void StarSystem::Update()
{
	UpdateCameraPro(&camera, control->GetCameraPostion(), control->GetCameraRotation(), 0.0f);
	control->Update();
}

void StarSystem::Draw2D()
{
}

void StarSystem::Draw3D()
{
	// Draw the primary star
	DrawSphere(Vector3{0, 0, 0}, 1, WHITE);

	// Orbit lines
	for (int i = 0; i < 10; i++)
	{
		DrawCircle3D(Vector3{0, 0, 0}, i * 5, Vector3{1, 0, 0}, 90, WHITE);
	}
}

void StarSystem::Unload()
{
}


