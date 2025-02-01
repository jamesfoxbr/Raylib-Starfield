#include "Space.h"

void Space::Draw3DBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
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

void Space::Draw3DBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint)
{
    Draw3DBillboardRec(camera, texture, { 0, 0, (float)texture.width, (float)texture.height }, position, { size, size }, tint);
}


Space::Space(Camera& camera)
	:
	camera(camera),
    gui(camera)
{
    random.seed(555);

    checkerboard = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    checkerTexture = LoadTextureFromImage(checkerboard);

    Vector3 lightPos = {0.0f, 10.0f, 0.0f};
    Color glowCol = WHITE;
    float glowInt = 1.0f;
}

Space::~Space()
{
    UnloadMesh(planeMesh); // Unload the mesh
    UnloadShader(shader);
    UnloadImage(checkerboard); // Unload image from RAM, not needed anymore
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
    camX = int(camera.position.x / chunkSize);
    camY = int(camera.position.y / chunkSize);
    camZ = int(camera.position.z / chunkSize);

    for (int dx = -chunkDrawDistance + camX; dx <= chunkDrawDistance + camX; dx++)
    {
        for (int dy = -chunkDrawDistance + camY; dy <= chunkDrawDistance + camY; dy++)
        {
            for (int dz = -chunkDrawDistance + camZ; dz <= chunkDrawDistance + camZ; dz++)
            {
                if (starfields.size() < 1)
                {
                    starfields.emplace_back(Starfield(numberOfStars, starDrawDistance, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize, random));
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
                        starfields.emplace_back(Starfield(numberOfStars, starDrawDistance, Vector3{(float)dx, (float)dy, (float)dz}, chunkSize, random));
                    }
                }
            }
        }
    }
}

const void Space::DrawStarNames(const Star& star)
{
    if (distance(camera.position, star.GetPosition()) < starDrawDistance / 2)
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

    transforms.clear();
    colors.clear();

    // Clear image
    ImageClearBackground(&image, {0, 0, 0, 0});
    //memset(image.data, 0, screenWidth * screenHeight * 4); // 4 bytes per pixel (RGBA)

    BeginShaderMode(shader);
    for (auto& starfield : starfields)
    {
        for (auto& star : starfield.GetStars())
        {
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
                transforms.push_back(star.GetTransform());
                colors.push_back(star.GetColor());

                DrawStarNames(star);

                // Draw billboard at star position and apply shader
                Draw3DBillboard(camera,checkerTexture, star.GetPosition(), 2, WHITE);
            }
        }
    }
    EndShaderMode();

    if (!(cubePos.x == 0 && cubePos.y == 0 && cubePos.z == 0))
    {
        DrawCubeWires(cubePos, 1.0f, 1.0f, 1.0f, SKYBLUE);
    }

    //BeginShaderMode(shader);
    //for (size_t i = 0; i < transforms.size(); ++i)
    //{
    //    material.maps[MATERIAL_MAP_DIFFUSE].color = colors[i];
    //    //material.maps[MATERIAL_MAP_DIFFUSE].texture = checkerTexture;

    //    // Pass the color to the shader
    //    //SetShaderValue(shader, GetShaderLocation(shader, "uColor"), &colors[i], SHADER_UNIFORM_VEC4);

    //    material.shader = shader;
    //    //DrawMesh(planeMesh, material, transforms[i]);
    //}
    //EndShaderMode();
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
    

    if (CheckCollisionPointCircle({(float)GetMouseX(), (float)GetMouseY()}, screenPos, starSize) && distance(star.GetPosition(), camera.position) < clickDistance)
    {
        gui.SetWindowOpen();
        return const_cast<Star*>(&star);
    }
    return nullptr;
}


