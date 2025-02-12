#include "StarSystem.h"

StarSystem::StarSystem()
{
	this->position = camera_ref.position;
}

StarSystem::~StarSystem()
{
}

void StarSystem::Init()
{
}

void StarSystem::Update()
{

}

void StarSystem::Draw2D()
{
}

void StarSystem::Draw3D()
{
	// Draw the primary star
	DrawSphere(position, 1, WHITE);

	// Orbit lines
	for (int i = 0; i < 10; i++)
	{
		DrawCircle3D(position, static_cast<float>(i * 5), Vector3{1, 0, 0}, 90, WHITE);
	}
}

void StarSystem::Unload()
{
}


