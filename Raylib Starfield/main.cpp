#include "Space.h"
#include "Globals.h"
#include "Window.h"
#include "Controls.h"
#include "imgui.h"
#include "rlImGui.h"	

int main() {
    Window window;
    Controls control;
    Space space(window.camera);

    rlImGuiSetup(true); 	// sets up ImGui with ether a dark or light default theme
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);


    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCameraPro(&window.camera, control.GetCameraPostion(), control.GetCameraRotation(), 0.0f);
        control.Update();

        BeginDrawing(); 
            ClearBackground(Color{(unsigned char)(clear_color.x * 255), (unsigned char)(clear_color.y * 255), (unsigned char)(clear_color.z * 255), (unsigned char)(clear_color.w * 255)});

            // 3D stuff go inside this area
            BeginMode3D(window.camera); 

                space.Update();
                space.Draw3D();

            // end of the 3d drawing area
            EndMode3D();
            // 2D stuff fixed to the screen space go in this area
            
                space.Draw2D();
                DrawCoordinates(window.camera);
                //targetCursor();
			    DrawDebugText("FPS: " + std::to_string(GetFPS()), 10, 30, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStarfields()) + " starfields", 10, 50, 20, RAYWHITE);
			    DrawDebugText(std::to_string(space.GetNumberOfStars()) + " stars", 10, 70, 20, RAYWHITE);

                rlImGuiBegin();			// starts the ImGui content mode. Make all ImGui calls after this
                {
                    
                    static float f = 0.0f;
                    static int counter = 0;

                    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                    ImGui::Checkbox("Another Window", &show_another_window);

                    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                        counter++;
                    ImGui::SameLine();
                    ImGui::Text("counter = %d", counter);

                    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                    ImGui::End();
                }
                rlImGuiEnd();			// ends the ImGui content mode. Make all ImGui calls before this

        EndDrawing(); 
    }

    rlImGuiShutdown();		// cleans up ImGui
    return 0;
}