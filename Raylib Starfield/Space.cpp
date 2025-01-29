#include "Space.h"

Space::Space(Camera& camera)
	:
	camera(camera)
{
}

Space::~Space()
{
}

void Space::Update()
{
	InstantiateStarfield();

	// Draw stars from the starfield class
	for (auto& starfield : starfields)
	{
		starfield.DrawStars(camera);
	}
}

int Space::GetNumberOfStars()
{
    int n = 0;

    for (auto& starfield : starfields)
    {
        n += starfield.GetNumberOfStars();
    }

    return n;
}

void Space::InstantiateStarfield()
{
    constexpr int numberOfStars     = 200; // number of stars in each chunk
	constexpr int chunkSize         = 100; // width, height and depth of the chunk
    constexpr int chunkDrawDistance = 2;   // how many chunks will draw in each direction from the central chunk de camera is at momenet
	constexpr int starDrawDistance  = 100; // how far the stars will be drawn from the camera

    int camX = int(camera.position.x / chunkSize);
    int camY = int(camera.position.y / chunkSize);
    int camZ = int(camera.position.z / chunkSize);

    for (int dx = -chunkDrawDistance + camX; dx <= chunkDrawDistance + camX; dx++)
    {
        for (int dy = -chunkDrawDistance + camY; dy <= chunkDrawDistance + camY; dy++)
        {
            for (int dz = -chunkDrawDistance + camZ; dz <= chunkDrawDistance + camZ; dz++)
            {
                if (starfields.size() < 1)
                {
                    Starfield starfield(numberOfStars, 50, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize);
                    starfields.push_back(starfield);
                }
                else
                {
                    bool positionOccupied = false;
                    for (auto it = starfields.begin(); it != starfields.end();)
                    {
                        if (floor(it->GetPosition().x / chunkSize) == dx && floor(it->GetPosition().y / chunkSize) == dy && floor(it->GetPosition().z / chunkSize) == dz)
                        {
                            positionOccupied = true;
                            break;
                        }

                        // Removing distant starfields
                        if (distance(it->GetPosition(), camera.position) > chunkSize * chunkDrawDistance * 2)
                        {
                            it = starfields.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    if (!positionOccupied)
                    {
                        Starfield starfield(numberOfStars, starDrawDistance, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize);
                        starfields.push_back(starfield);
                    }
                }
            }
        }
    }
}


