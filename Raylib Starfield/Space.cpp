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
    UpdateLocalStarArray();

    for (const auto* star : starsPtr)
    {
        DrawStars(star);
        StarClicked(star);
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
    int numberOfStars               = random() % 200; // number of stars in each chunk
	constexpr int chunkSize         = 100;            // width, height and depth of the chunk
    constexpr int chunkDrawDistance = 2;              // how many chunks will draw in each direction from the central chunk de camera is at momenet
	constexpr int starDrawDistance  = 100;            // how far the stars will be drawn from the camera

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
                        if (distance(it->GetPosition(), {camera.position}) > chunkSize * chunkDrawDistance * 3)
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

void Space::UpdateLocalStarArray()
{
    std::unordered_set<Star*> newStarsPtr;

    for (const auto& starfield : starfields)
    {
        for (auto* star : starfield.GetStars())
        {
            newStarsPtr.insert(star);
        }
    }

    starsPtr.assign(newStarsPtr.begin(), newStarsPtr.end());
}

void Space::DrawStars(const Star* star)
{
    if (star == nullptr) return; // Skip null pointers

    constexpr int starDrawDistance = 100; // how far the stars will be drawn from the camera
    Vector3 cameraForward          = Vector3Subtract(camera.target, camera.position);
    cameraForward                  = Vector3Normalize(cameraForward); // Get forward direction

    //// Draw wireframe cube to represent the area of a starfield
    //Vector3 starfieldPos = starfield.GetPosition();
    //Vector3 cubeSize = {100.0f, 100.0f, 100.0f}; // Assuming chunkSize is 100
    //DrawCubeWires(starfieldPos, cubeSize.x, cubeSize.y, cubeSize.z, WHITE);

    
    Vector3 toStar = Vector3Subtract(star->GetPosition(), camera.position);
    float dotProduct = Vector3DotProduct(cameraForward, toStar);

    // Check if the star is in front of the camera
    if (dotProduct <= 0) return; // Skip stars behind the camera

    if (distance(camera.position, star->GetPosition()) > starDrawDistance)
    {
        DrawPoint3D(star->GetPosition(), star->GetColor());
    }
    else
    {
        Matrix transform = MatrixTranslate(star->GetPosition().x, star->GetPosition().y, star->GetPosition().z);
        material.maps[MATERIAL_MAP_DIFFUSE].color = star->GetColor();
        DrawMesh(sphereMesh, material, transform);

        if (distance(camera.position, star->GetPosition()) < starDrawDistance / 2)
        {
            // Draw the star name above the sphere
            Vector3 namePosition = star->GetPosition();
            namePosition.y += 0.5f; // Adjust the height above the sphere
            Vector2 screenPos = GetWorldToScreen(namePosition, camera);
            int fontSize = 20; // Define the font size
            EndMode3D();
                DrawText(star->GetName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), fontSize, WHITE);
            BeginMode3D(camera);
        }
    }
}

const void Space::StarClicked(const Star* star)
{
    // Check if a star is clicked
    if (star == nullptr) return; // Skip null pointers

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 screenPos = GetWorldToScreen(star->GetPosition(), camera);
        const float starSize = 20.0f;  // Use the star's size for collision detection
        const float clickDistance = 100.0f; // How far the mouse can be from the star to click it

        if (CheckCollisionPointCircle({screenWidth / 2, screenHeight / 2}, screenPos, starSize) && distance(star->GetPosition(), camera.position) < clickDistance)
        {
            DrawCube(star->GetPosition(), 1.0f, 1.0f, 1.0f, RED);
            std::cout << "Star " << star->GetName() << " clicked!" << std::endl;
        }
    }
}




