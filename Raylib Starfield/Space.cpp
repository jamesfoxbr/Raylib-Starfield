#include "Space.h"

void Space::Draw3DBillboardRec(Camera& camera, Texture2D& texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
{
    rlPushMatrix();

    // get the camera view matrix
    Matrix mat = MatrixInvert(MatrixLookAt(camera.position, camera.target, camera.up));
    // peel off just the rotation
    Quaternion quat = QuaternionFromMatrix(mat);
    mat = QuaternionToMatrix(quat);

    // apply just the rotation
    rlMultMatrixf(MatrixToFloat(mat));

    // translate backwards in the inverse rotated matrix to put the item where it goes in world space
    position = Vector3Transform(position, MatrixInvert(mat));
    rlTranslatef(position.x, position.y, position.z);

    // draw the billboard
    float width = size.x / 2;
    float height = size.y / 2;

    rlCheckRenderBatchLimit(6);

    rlSetTexture(texture.id);

    // draw quad
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer

    rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(-width, -height, 0);  // Bottom Left Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(+width, -height, 0);  // Bottom Right Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
    rlVertex3f(+width, +height, 0);  // Top Right Of The Texture and Quad

    rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
    rlVertex3f(-width, +height, 0);  // Top Left Of The Texture and Quad

    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}

void Space::Draw3DBillboard(Camera& camera, Texture2D& texture, Vector3 position, float size, Color tint)
{
    Draw3DBillboardRec(camera, texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)}, position, {size, size}, tint);
}


Space::Space(Camera& camera)
	:
	camera(camera),
    gui(camera)
{
    random.seed(555);

    checkerboard = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    checkerTexture = LoadTextureFromImage(checkerboard);
    UnloadImage(checkerboard); // Unload image from RAM, not needed anymore
}

Space::~Space()
{
    UnloadMesh(planeMesh); // Unload the mesh
    UnloadShader(shader);
    UnloadTexture(checkerTexture);
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
    camX = static_cast<int>(camera.position.x / chunkSize);
    camY = static_cast<int>(camera.position.y / chunkSize);
    camZ = static_cast<int>(camera.position.z / chunkSize);

    std::unordered_set<Vector3, Vector3Hash> activeChunks;

    for (int dx = -chunkDrawDistance + camX; dx <= chunkDrawDistance + camX; dx++)
    {
        for (int dy = -chunkDrawDistance + camY; dy <= chunkDrawDistance + camY; dy++)
        {
            for (int dz = -chunkDrawDistance + camZ; dz <= chunkDrawDistance + camZ; dz++)
            {
                activeChunks.insert(Vector3{(float)dx, (float)dy, (float)dz});
            }
        }
    }

    // Remove starfields that are outside the active chunk range
    auto it = starfields.begin();
    while (it != starfields.end())
    {
        Vector3 pos = it->GetPosition();
        int starX = static_cast<int>(pos.x / chunkSize);
        int starY = static_cast<int>(pos.y / chunkSize);
        int starZ = static_cast<int>(pos.z / chunkSize);

        if (activeChunks.find(Vector3{(float)starX, (float)starY, (float)starZ}) == activeChunks.end())
        {
            it = starfields.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Add new starfields in missing chunks
    for (const auto& chunk : activeChunks)
    {
        bool exists = std::any_of(starfields.begin(), starfields.end(), [&](const Starfield& s) {
            Vector3 pos = s.GetPosition();
            return static_cast<int>(pos.x / chunkSize) == static_cast<int>(chunk.x) &&
                static_cast<int>(pos.y / chunkSize) == static_cast<int>(chunk.y) &&
                static_cast<int>(pos.z / chunkSize) == static_cast<int>(chunk.z);
            });

        if (!exists)
        {
            starfields.emplace_back(Starfield(random() % numberOfStars, starDrawDistance, chunk, chunkSize, random));
        }
    }
}


const void Space::DrawStarNames(const Star& star)
{
    if (distance(camera.position, const_cast<Vector3&>(star.GetPosition())) < starDrawDistance / 4)
    {
        // Draw the star name above the sphere
        Position3D = star.GetPosition();
        Position3D.y += 0.5f; // Adjust the height above the sphere
        const Vector2 screenPos = GetWorldToScreen(Position3D, camera);
        const int width = int(star.GetName().length() * 8);
        const int weight = 16;
        const int adjustX = -4;
        const int adjustY = -4;
        ImageDrawRectangle(&image, static_cast<int>(screenPos.x) + adjustX, static_cast<int>(screenPos.y) + adjustY, width, weight, BLACK);
        ImageDrawRectangleLines(&image, {screenPos.x + adjustX, screenPos.y + adjustY, (float)width, weight}, 2, RED);

        ImageDrawText(&image, star.GetName().c_str(), static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), 10, WHITE);
    }
}

void Space::Draw3D()
{
    Vector3 cameraForward = Vector3Subtract(camera.target, camera.position);
    cameraForward = Vector3Normalize(cameraForward); // Get forward direction

    BillColors.clear();
    BillPositions.clear();

    std::string starName;
    Vector3 starPosition;

    // Clear image
    ImageClearBackground(&image, {0, 0, 0, 0});
        
    for (const auto& starfield : starfields)
    {
        for (const auto& star : starfield.GetStars())
        {
            starName = star.GetName();
            starPosition = star.GetPosition();

            if (distance(camera.position, starPosition) > starDrawDistance * 3) continue;

            // detects the star being clicked
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsStarClicked(star) != nullptr)
            {
                cubePos = star.GetPosition();
                
                selectedStar = IsStarClicked(star);
                gui.SetStarName(selectedStar->GetName());
                gui.SetStarClass(selectedStar->GetSpectralClass());
            }
            else
            {
                selectedStar = nullptr;
            }

            Vector3 toStar = Vector3Subtract(starPosition, camera.position);
            float dotProduct = Vector3DotProduct(cameraForward, toStar);

            // Check if the star is in front of the camera
            if (dotProduct <= 0) continue; // Skip stars behind the camera

            if (distance(camera.position, starPosition) > starDrawDistance)
            {
                Position3D = starPosition;
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

                DrawStarNames(star);

                // Draw billboard at star position and apply shader
                BillColors.push_back(star.GetColor());
                BillPositions.push_back(starPosition);
            }
        }
    }
    

    if (!(cubePos.x == 0 && cubePos.y == 0 && cubePos.z == 0))
    {
        DrawCubeWires(cubePos, 1.0f, 1.0f, 1.0f, SKYBLUE);
    }

    BeginShaderMode(shader);
    for (size_t i = 0; i < BillPositions.size(); ++i)
    {
        int loc = GetShaderLocation(shader, "myAlpha");
        const float alpha = 1.0f;
        SetShaderValue(shader, loc, &alpha, RL_SHADER_ATTRIB_FLOAT);
        Draw3DBillboard(camera, checkerTexture, BillPositions[i], 4.0f, BillColors[i]);
    }
    EndShaderMode();
}

void Space::Draw2D()
{
    UpdateTexture(texture, image.data);  // Send updated image to GPU (one call)
    DrawTexture(texture, 0, 0, WHITE);
    gui.DrawInterface();
}

Star* Space::IsStarClicked(const Star& star) 
{
    Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera);
    const float starSize = 20.0f;  // Use the star's size for collision detection
    const float clickDistance = 100.0f; // How far the mouse can be from the star to click it
    

    if (CheckCollisionPointCircle({(float)GetMouseX(), (float)GetMouseY()}, screenPos, starSize) && distance(const_cast<Vector3&>(star.GetPosition()), camera.position) < clickDistance)
    {
        gui.SetWindowOpen();
        return const_cast<Star*>(&star);
    }
    return nullptr;
}


