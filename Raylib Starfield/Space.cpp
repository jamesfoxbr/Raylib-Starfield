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

void Space::InstantiateStarfield()
{
    int camX = int(camera.position.x / 100);
    int camY = int(camera.position.y / 100);
    int camZ = int(camera.position.z / 100);

    constexpr int numberOfStars = 50;
	constexpr int chunkSize     = 50;
    constexpr int chunkDistance = 2;

    for (int dx = -chunkDistance + camX; dx <= chunkDistance + camX; dx++)
    {
        for (int dy = -chunkDistance + camY; dy <= chunkDistance + camY; dy++)
        {
            for (int dz = -chunkDistance + camZ; dz <= chunkDistance + camZ; dz++)
            {
                if (starfields.size() < 27)
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
                        if (distance(it->GetPosition(), camera.position) > chunkSize * 2)
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
                        Starfield starfield(numberOfStars, 50, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize);
                        starfields.push_back(starfield);
                    }
                }
            }
        }
    }
}


