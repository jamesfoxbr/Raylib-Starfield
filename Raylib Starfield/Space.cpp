#include "Space.h"

Space::Space(Camera& camera)
	:
	camera(camera)
{
	InstantiateStarfield();
}

Space::~Space()
{
}

void Space::Update()
{
	for (auto& starfield : starfields)
	{
		starfield.DrawStars(camera);
	}
}

void Space::InstantiateStarfield()
{
	starfields.clear();

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			for (int dz = -1; dz <= 1; dz++)
			{
				Starfield starfield(1000, 50, Vector3{(float)dx, (float)dy, (float)dz});
				starfields.push_back(starfield);
			}
		}
	}
}

void Space::UnloadFarChunks()
{
}
