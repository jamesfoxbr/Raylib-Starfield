#include "Space.h"

Space::Space(Camera& camera)
	:
	camera(camera)
{
    random.seed(555);
}

Space::~Space()
{
    UnloadMesh(sphereMesh); // Unload the mesh
}

void Space::Update()
{
	InstantiateStarfield();
    DrawStars();

	//for (auto& starfield : starfields)
	//{
	//	starfield.DrawStars(camera);    // Draw stars from the starfield class

    //       if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && starfield.IsStarClicked(camera) != nullptr)
     //       {
	//		selectedStar = starfield.IsStarClicked(camera);
	//		std::cout << "Star " << selectedStar->GetName() << " clicked!" << std::endl;
    //       }
    //       else
    //       {
	//		selectedStar = nullptr;
    //       }
	//}
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
                    Starfield starfield(numberOfStars, starDrawDistance, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize, random);
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
                        Starfield starfield(numberOfStars, starDrawDistance, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize, random);
                        starfields.push_back(starfield);
                    }
                }
            }
        }
    }
}

void Space::DrawStars()
{
    constexpr int starDrawDistance = 100; // how far the stars will be drawn from the camera
    Vector3 cameraForward = Vector3Subtract(camera.target, camera.position);
    cameraForward = Vector3Normalize(cameraForward); // Get forward direction

    std::vector<Matrix> transforms;
    std::vector<Color> colors;

    for (auto& starfield : starfields)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && starfield.IsStarClicked(camera) != nullptr)
        {
            selectedStar = starfield.IsStarClicked(camera);
            std::cout << "Star " << selectedStar->GetName() << " clicked!" << std::endl;
        }
        else
        {
            selectedStar = nullptr;
        }

        for (auto& star : starfield.GetStars())
        {
            Vector3 toStar = Vector3Subtract(star.GetPosition(), camera.position);
            float dotProduct = Vector3DotProduct(cameraForward, toStar);

            // Check if the star is in front of the camera
            if (dotProduct <= 0) continue; // Skip stars behind the camera

            if (distance(camera.position, star.GetPosition()) > starDrawDistance)
            {
                DrawPoint3D(star.GetPosition(), star.GetColor());
            }
            else
            {
                Matrix transform = MatrixTranslate(star.GetPosition().x, star.GetPosition().y, star.GetPosition().z);
                transforms.push_back(transform);
                colors.push_back(star.GetColor());

                if (distance(camera.position, star.GetPosition()) < starDrawDistance / 2)
                {
                    // Draw the star name above the sphere
                    Vector3 namePosition = star.GetPosition();
                    namePosition.y += 0.5f; // Adjust the height above the sphere
                    Vector2 screenPos = GetWorldToScreen(namePosition, camera);
                    int fontSize = 20; // Define the font size
                    EndMode3D();
                    DrawText(star.GetName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), fontSize, WHITE);
                    BeginMode3D(camera);
                }
            }
        }
    }

    // Draw all spheres in one draw call
    for (size_t i = 0; i < transforms.size(); ++i)
    {
        material.maps[MATERIAL_MAP_DIFFUSE].color = colors[i];
        DrawMesh(sphereMesh, material, transforms[i]);
    }
}




