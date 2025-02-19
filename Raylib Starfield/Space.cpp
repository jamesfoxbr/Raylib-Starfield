// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Space.cpp
// Description: Main entry point for the Raylib Starfield project.
//
// License: Proprietary
// 
// This software is the confidential and proprietary information of Marcio Marchado Ribeiro
// ("Confidential Information"). You shall not disclose such Confidential Information and shall use
// it only in accordance with the terms of the license agreement you entered into with Marcio Marchado Ribeiro.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Author: Marcio Marchado Ribeiro
// Version: 0.1
// --------------------------------------------------------------------------------------------

#include "Space.h"

Space::Space()
{  
	loadedScene = SPACE;						 // Set the loaded scene to SPACE
	camera_ref.position = savedCameraPosition;   // Set the camera position to the saved position
    camera_ref.target = savedCameraTarget;       // Set the camera target to the saved target
    starfields = new std::vector<Starfield>();   // Initialize starfields as a vector
    random.seed(SEED);                           // Seed the random number generator

    // Material for the cube skybox
    SetMaterialTexture(&cubeModel.materials[0],
                      MATERIAL_MAP_DIFFUSE, 
                      resourceManager_ref.GetTexture("resources/images/skybox.png"));

    // Rotate the skybox 90 degrees around the Y-axis
    Matrix rotation = MatrixRotateX(PI / 2);
    cubeModel.transform = MatrixMultiply(cubeModel.transform, rotation);

    InstantiateStarfield();
}

Space::~Space()  
{  
}

void Space::Init()
{
}

void Space::Unload()
{
   // De-Initialization  
   //-------------------------------------------------------------------------------------  
    selectedStarPtr = nullptr; // Clear the selected star pointer
    starfields->clear();    // Clear the starfield vector/array
    delete starfields;      // Correctly delete the vector
}

void Space::Update()
{
    if(MovingBetweenChunks())
    {
        InstantiateStarfield();
    }
}

int Space::GetNumberOfStars()
{
    int n = 0;

    for (auto& starfield : *starfields)
    {
        n += starfield.GetNumberOfStars();
    }

    return n;
}

void Space::InstantiateStarfield()
{
    activeChunks.clear();

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
    auto it = starfields->begin();
    while (it != starfields->end())
    {
        Vector3 pos = it->GetPosition();                 // Get the position of the starfield
        int starX = static_cast<int>(pos.x / chunkSize); // Get the chunk x position
        int starY = static_cast<int>(pos.y / chunkSize); // Get the chunk y position
        int starZ = static_cast<int>(pos.z / chunkSize); // Get the chunk z position

        if (activeChunks.find(Vector3{(float)starX, (float)starY, (float)starZ}) == activeChunks.end()) 
        {
            it->GetStars().clear();
            it = starfields->erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Add new starfields in missing chunks
    for (const auto& chunk : activeChunks)
    {
        bool exists = std::any_of(starfields->begin(), starfields->end(), [&](const Starfield& s) {
            Vector3 pos = s.GetPosition();
            return static_cast<int>(pos.x / chunkSize) == static_cast<int>(chunk.x) &&
                static_cast<int>(pos.y / chunkSize) == static_cast<int>(chunk.y) &&
                static_cast<int>(pos.z / chunkSize) == static_cast<int>(chunk.z);
            });

        if (!exists)
        {
            // Add a new starfield chunk if it doesn't exist
            starfields->emplace_back(Starfield(random() % numberOfStars, starDrawDistance, chunk, chunkSize, random));
        }
    }
}

bool Space::MovingBetweenChunks()
{
    newCamX = static_cast<int>(camera_ref.position.x / chunkSize);
    newCamY = static_cast<int>(camera_ref.position.y / chunkSize);
    newCamZ = static_cast<int>(camera_ref.position.z / chunkSize);

    // Only update starfields if the camera has moved to a new chunk
    if (newCamX == camX && newCamY == camY && newCamZ == camZ) return true;

    camX = newCamX;
    camY = newCamY;
    camZ = newCamZ;

    return false;
}

void Space::Draw3D()
{
    // We are inside the cube, we need to disable backface culling!
	rlDisableBackfaceCulling();     // Disable backface culling to see the inside of the cube
	rlDisableDepthMask();	        // Disable depth writing to see the inside of the cube
	BeginBlendMode(BLEND_ADDITIVE); // Enable additive blending for the stars

    DrawModel(cubeModel, camera_ref.position, 100.0f, WHITE);
    
    // --------------------------------------------------------------------------------------
    cameraForward = Vector3Subtract(camera_ref.target, camera_ref.position);
    cameraForward = Vector3Normalize(cameraForward); // Get forward direction

    // --------------------------------------------------------------------------------------
	BillColors.clear();    // Clear the billboard colors vector
	BillPositions.clear(); // Clear the billboard positions vector
        
    for (const auto& starfield : *starfields)
    {
        for (const auto& star : starfield.GetStars())
        {
            const std::string starName = star.GetName();
            const Vector3 starPosition = star.GetPosition();

            // Check if the star is in front of the camera
            Vector3 toStar = Vector3Subtract(starPosition, camera_ref.position);
            float dotProduct = Vector3DotProduct(cameraForward, toStar);

            if (dotProduct <= 0) continue; // Skip stars behind the camera

            // detects the star being clicked to draw a selection wire cube on it
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsStarClicked(star) != nullptr)
            {
                cubePos = star.GetPosition();
                
                selectedStarPtr = IsStarClicked(star);
				gui_ptr->SetStarName(selectedStarPtr->GetName());
				gui_ptr->SetStarClass(selectedStarPtr->GetSpectralClass());
                gui_ptr->SetWindowOpen();
            }

            if (distance(camera_ref.position, starPosition) < starDrawDistance)
            {
                // Draw billboard at star position and apply shader
                BillColors.push_back(star.GetColor());
                BillPositions.push_back(starPosition);
            }
        }
    }
    
    // --------------------------------------------------------------------------------------
    // Draw the billboard to apply the star shader to make it shiny    
    BeginShaderMode(shader);
    for (size_t i = 0; i < BillPositions.size(); ++i)
    {
        int loc = GetShaderLocation(shader, "myAlpha");
        const float alpha = 1.0f;
        SetShaderValue(shader, loc, &alpha, RL_SHADER_ATTRIB_FLOAT);
        Draw3DBillboard(checkerBoardTexture, BillPositions[i], 4.0f, BillColors[i]);
    }

	EndShaderMode();           // End the shader mode

	EndBlendMode();            // Disable additive blending for the stars
	rlEnableDepthMask();       // Enable depth writing to not see the inside of the cube
	rlEnableBackfaceCulling(); // Enable backface culling to not see the inside of the cube

    // --------------------------------------------------------------------------------------
    // Draw the selection cube
    if (!(cubePos.x == 0 && cubePos.y == 0 && cubePos.z == 0))
    {
        DrawCubeWires(cubePos, 1.0f, 1.0f, 1.0f, SKYBLUE);
    }
}

void Space::DrawHUD()
{
    // Get the camera's rotation matrix
    Matrix rotationMatrix = MatrixLookAt(camera_ref.position, camera_ref.target, camera_ref.up);
    Quaternion rotation = QuaternionFromMatrix(rotationMatrix);

    // Convert quaternion to Euler angles
    Vector3 euler = QuaternionToEuler(rotation);

    // Convert radians to degrees
    euler.x *= RAD2DEG;
    euler.y *= RAD2DEG;
    euler.z *= RAD2DEG;

    // Draw the HUD
    const int fontSize = 20;
    const int padding = 10;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawText(TextFormat("Rotation X: %.2f", euler.x), padding, screenHeight - 3 * (fontSize + padding), fontSize, RAYWHITE);
    DrawText(TextFormat("Rotation Y: %.2f", euler.y), padding, screenHeight - 2 * (fontSize + padding), fontSize, RAYWHITE);
    DrawText(TextFormat("Rotation Z: %.2f", euler.z), padding, screenHeight - (fontSize + padding), fontSize, RAYWHITE);

    // Draw the fighter airplane graphical HUD
    const int centerX = screenWidth / 2;
    const int centerY = screenHeight / 2;
    const int hudSize = 100;

    // Draw central crosshair
    DrawLine(centerX - 10, centerY, centerX + 10, centerY, GREEN);
    DrawLine(centerX, centerY - 10, centerX, centerY + 10, GREEN);

    // Draw horizontal angle lines
    for (int i = -hudSize; i <= hudSize; i += 20)
    {
        DrawLine(centerX - hudSize, centerY + i, centerX + hudSize, centerY + i, GREEN);
        DrawText(TextFormat("%d", i), centerX + hudSize + 5, centerY + i - 5, fontSize, GREEN);
    }

    // Draw vertical angle lines
    for (int i = -hudSize; i <= hudSize; i += 20)
    {
        DrawLine(centerX + i, centerY - hudSize, centerX + i, centerY + hudSize, GREEN);
        DrawText(TextFormat("%d", i), centerX + i - 10, centerY - hudSize - 20, fontSize, GREEN);
    }
}

void Space::Draw2D()
{
    // Draw names above star systems
    for (const auto& starfield : *starfields)
    {
        for (const auto& star : starfield.GetStars())
        {
            // Check if the star is in front of the camera
            Vector3 toStar = Vector3Subtract(star.GetPosition(), camera_ref.position);
            float dotProduct = Vector3DotProduct(cameraForward, toStar);

            if (dotProduct <= 0) continue; // Skip stars behind the camera

            if (distance(camera_ref.position, star.GetPosition()) < starDrawDistance / 4)
            {
                const Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera_ref);
                const int fontSize = 18;
                DrawText(star.GetName().c_str(), static_cast<int>(screenPos.x) - 25, static_cast<int>(screenPos.y) - 25, fontSize, RAYWHITE);
            }
        }
    }

    //DrawHUD();
}

Star* Space::IsStarClicked(const Star& star) 
{
    Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera_ref);
    const float starSize = 20.0f;                 // Use the star's size for collision detection
    const float clickDistance = starDrawDistance; // How far the mouse can be from the star to click it
    

    if (CheckCollisionPointCircle({(float)GetMouseX(), (float)GetMouseY()}, screenPos, starSize) && distance(const_cast<Vector3&>(star.GetPosition()), camera_ref.position) < clickDistance)
    {
        return const_cast<Star*>(&star);
    }
    return nullptr;
}

void Space::Draw3DBillboardRec(Texture2D& texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
{
    rlPushMatrix();

    // get the camera view matrix
    Matrix mat = MatrixInvert(MatrixLookAt(camera_ref.position, camera_ref.target, camera_ref.up));
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

void Space::Draw3DBillboard(Texture2D& texture, Vector3 position, float size, Color tint)
{
    Draw3DBillboardRec(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)}, position, {size, size}, tint);
}