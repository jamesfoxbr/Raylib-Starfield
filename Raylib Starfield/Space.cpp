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
                        if (distance(it->GetPosition(), camera.position) > chunkSize * chunkDrawDistance * 2.5)
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

void Space::Draw3D()
{
    constexpr int starDrawDistance = 100; // how far the stars will be drawn from the camera
    Vector3 cameraForward = Vector3Subtract(camera.target, camera.position);
    cameraForward = Vector3Normalize(cameraForward); // Get forward direction

   

    transforms.clear();
    colors.clear();

    // Clear image
    memset(image.data, 0, screenWidth * screenHeight * 4); // 4 bytes per pixel (RGBA)

    for (auto& starfield : starfields)
    {
        for (auto& star : starfield.GetStars())
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsStarClicked(star) != nullptr)
            {
                selectedStar = IsStarClicked(star);
                std::cout << "Star " << selectedStar->GetName() << " clicked!" << std::endl;
            }
            else
            {
                selectedStar = nullptr;
            }

            Vector3 toStar = Vector3Subtract(star.GetPosition(), camera.position);
            float dotProduct = Vector3DotProduct(cameraForward, toStar);

            // Check if the star is in front of the camera
            if (dotProduct <= 0) continue; // Skip stars behind the camera

            if (distance(camera.position, star.GetPosition()) > starDrawDistance)
            {
                Position3D = star.GetPosition();
                screenPos = GetWorldToScreen(Position3D, camera);
                const int x = static_cast<int>(screenPos.x);
                const int y = static_cast<int>(screenPos.y);

                if (x > 0 && x < screenWidth && y > 0 && y < screenHeight)
                {
                    ImageDrawPixel(&image, x, y, star.GetColor());
                }
            }
            else // Draw closer stars
            {
                const Matrix transform = MatrixTranslate(star.GetPosition().x, star.GetPosition().y, star.GetPosition().z);
                transforms.push_back(transform);
                colors.push_back(star.GetColor());

                if (distance(camera.position, star.GetPosition()) < starDrawDistance / 2)
                {
                    // Draw the star name above the sphere
                    Position3D = star.GetPosition();
                    Position3D.y += 0.5f; // Adjust the height above the sphere
                    const Vector2 screenPos = GetWorldToScreen(Position3D, camera);
                    //EndMode3D();
                    ImageDrawText(&image, star.GetName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), 10, WHITE);
                    //BeginMode3D(camera);
                    //ImageDrawText(&image, star.GetName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), fontSize, WHITE);
                }
            }
        }
    }

    for (size_t i = 0; i < transforms.size(); ++i)
    {
        material.maps[MATERIAL_MAP_DIFFUSE].color = colors[i];
        DrawMesh(sphereMesh, material, transforms[i]);
    }
}

void Space::Draw2D()
{
    UpdateTexture(texture, image.data);  // Send updated image to GPU (one call)
    DrawTexture(texture, 0, 0, WHITE);
}

Star* Space::IsStarClicked(const Star& star) const
{
    Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera);
    const float starSize = 20.0f;  // Use the star's size for collision detection
    const float clickDistance = 100.0f; // How far the mouse can be from the star to click it

    if (CheckCollisionPointCircle({(float)GetMouseX(), (float)GetMouseY()}, screenPos, starSize) && distance(star.GetPosition(), camera.position) < clickDistance)
    {
        DrawCube(star.GetPosition(), 1.0f, 1.0f, 1.0f, RED);
        return const_cast<Star*>(&star);
    }
}


