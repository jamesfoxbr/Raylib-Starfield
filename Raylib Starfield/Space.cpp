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
    std::cout << starfields.size() << "\n";
    int camX = camera.position.x / 100;
    int camY = camera.position.y / 100;
    int camZ = camera.position.z / 100;

    const int numberOfStars = 100;
    const int maxChunks = 35;
	const int chunkSize = 100;

    for (int dx = -1 + camX; dx <= 1 + camX; dx++)
    {
        for (int dy = -1 + camY; dy <= 1 + camY; dy++)
        {
            for (int dz = -1 + camZ; dz <= 1 + camZ; dz++)
            {
                if (starfields.size() < 27)
                {
                    Starfield starfield(numberOfStars, 50, Vector3{(float)dx, (float)dy, (float)dz});
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
                        if (distance(it->GetPosition(), camera.position) > chunkSize)
                        {
                            it = starfields.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                    if (!positionOccupied && starfields.size() < maxChunks)
                    {
                        Starfield starfield(numberOfStars, 50, Vector3{(float)dx, (float)dy, (float)dz});
                        starfields.push_back(starfield);
                    }
                }
            }
        }
    }
}


