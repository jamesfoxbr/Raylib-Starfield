#include "Space.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"	

// Generate cubemap (6 faces) from equirectangular (panorama) texture
static TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format);

int main() {
    Window window;
    Controls control;
    Space space(window.camera);

    // Load skybox model
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    
    Model skybox = LoadModel("cube.obj");
    Texture2D texture = LoadTexture("skybox.png");
    SetMaterialTexture(&skybox.materials[0], MATERIAL_MAP_DIFFUSE, texture);

    // Rotate the skybox 90 degrees around the Y-axis
    Matrix rotation = MatrixRotateX(PI / 2);
    skybox.transform = MatrixMultiply(skybox.transform, rotation);

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCameraPro(&window.camera, control.GetCameraPostion(), control.GetCameraRotation(), 0.0f);
        control.Update();

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

            space.Update();
            
            BeginMode3D(window.camera);
            {
                // We are inside the cube, we need to disable backface culling!
                rlDisableBackfaceCulling();
                rlDisableDepthMask();
                DrawModel(skybox, window.camera.position, 100.0f, WHITE);
                rlEnableBackfaceCulling();
                rlEnableDepthMask();

                space.Draw3D();
            }
            EndMode3D();

            space.Draw2D();

            DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
            DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);
        }
        EndDrawing(); 
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(skybox.materials[0].shader);
    UnloadTexture(skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);

    UnloadModel(skybox);        // Unload skybox model

    return 0;
}

// Generate cubemap texture from HDR texture
static TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format)
{
    TextureCubemap cubemap = {0};

    rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

    // STEP 1: Setup framebuffer
    //------------------------------------------------------------------------------------------
    unsigned int rbo = rlLoadTextureDepth(size, size, true);
    cubemap.id = rlLoadTextureCubemap(0, size, format, 1);

    unsigned int fbo = rlLoadFramebuffer();
    rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    // Check if framebuffer is complete with attachments (valid)
    if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
    //------------------------------------------------------------------------------------------

    // STEP 2: Draw to framebuffer
    //------------------------------------------------------------------------------------------
    // NOTE: Shader is used to convert HDR equirectangular environment map to cubemap equivalent (6 faces)
    rlEnableShader(shader.id);

    // Define projection matrix and send it to shader
    Matrix matFboProjection = MatrixPerspective(90.0 * DEG2RAD, 1.0, rlGetCullDistanceNear(), rlGetCullDistanceFar());
    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

    // Define view matrix for every side of the cubemap
    Matrix fboViews[6] = {
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { 1.0f,  0.0f,  0.0f }, { 0.0f, -1.0f,  0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { -1.0f,  0.0f,  0.0f}, { 0.0f, -1.0f,  0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f,  0.0f,  1.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f, -1.0f,  0.0f }, { 0.0f,  0.0f, -1.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f,  0.0f,  1.0f }, { 0.0f, -1.0f,  0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f }, { 0.0f,  0.0f, -1.0f }, { 0.0f, -1.0f,  0.0f })
    };

    rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions

    // Activate and enable texture for drawing to cubemap faces
    rlActiveTextureSlot(0);
    rlEnableTexture(panorama.id);

    for (int i = 0; i < 6; i++)
    {
        // Set the view matrix for the current cube face
        rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

        // Select the current cubemap face attachment for the fbo
        // WARNING: This function by default enables->attach->disables fbo!!!
        rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rlEnableFramebuffer(fbo);

        // Load and draw a cube, it uses the current enabled texture
        rlClearScreenBuffers();
        rlLoadDrawCube();

        // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
        // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
        // TODO: Investigate this issue...
        //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
        //rlClearScreenBuffers();
        //DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
        //rlDrawRenderBatchActive();
    }
    //------------------------------------------------------------------------------------------

    // STEP 3: Unload framebuffer and reset state
    //------------------------------------------------------------------------------------------
    rlDisableShader();          // Unbind shader
    rlDisableTexture();         // Unbind texture
    rlDisableFramebuffer();     // Unbind framebuffer
    rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

    // Reset viewport dimensions to default
    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();
    //------------------------------------------------------------------------------------------

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}

