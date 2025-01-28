#include "Space.h"

Space::Space(Camera& camera)
	:
	camera(camera)
{
	Starfield starfield(50000, 50);
	starfields.push_back(starfield);
}

Space::~Space()
{
}

void Space::Update()
{
	starfields[0].DrawStars(camera);
}

void Space::UpdateChunk()
{
}

void Space::ProcessChunk()
{
}

void Space::InstantiateStarfield(Vector3 chunkCoords)
{
}

void Space::UnloadFarChunks(Vector3 chunkCoords)
{
}
