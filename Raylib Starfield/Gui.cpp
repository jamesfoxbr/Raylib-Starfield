#include "Gui.h"

Gui::Gui(Camera& camera)
    :
    camera(camera)
{
	rlImGuiSetup(true); 	// sets up ImGui with ether a dark or light default theme
}

Gui::~Gui()
{
    rlImGuiShutdown();		// cleans up ImGui
}

void Gui::DrawInterface()
{
    rlImGuiBegin();			// starts the ImGui content mode. Make all ImGui calls after this
   
    // Debug Window
    ImGui::Begin("DEBUG INFORMATION");
    //ImGui::Text(("ExitGame: " + std::to_string(exitGame)).c_str());
    ImGui::End();

    // Coordinates window
    float windowSize = 200;
    ImGui::SetNextWindowSize({400, 72});
    ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowSize, 4});
    ImGui::Begin("COORDINATES", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Text(("Coordinates: X " + std::to_string((int)camera.position.x) +
        " / Y " + std::to_string((int)camera.position.y)
        + " / Z " + std::to_string((int)camera.position.z)).c_str());

    int coordinates[3] = {(int)camera.position.x, (int)camera.position.y, (int)camera.position.z};
    if (ImGui::InputInt3("Input Coordinates", coordinates))
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
        {
            camera.position.x = (float)coordinates[0];
            camera.position.y = (float)coordinates[1];
            camera.position.z = (float)coordinates[2];
            camera.target     = Vector3{0.0f, 0.0f, 0.0f};
        }

    ImGui::End();

    // Star System Information Window
    if (windowOpen)
    {
        ImGui::SetWindowSize({200, 100});
        ImGui::Begin("STAR INFORMATION", &windowOpen, ImGuiWindowFlags_NoResize);  
        ImGui::Text(("Star Name: " + selectedStar).c_str());   

        char s[23] = "Star Spectral Class: ";
        s[21] = *starClass;
        ImGui::Text(s);   

        
        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //ImGui::Checkbox("Another Window", &show_another_window);

        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
    
    rlImGuiEnd();			// ends the ImGui content mode. Make all ImGui calls before this
}

void Gui::SetStarName(std::string name)
{
    selectedStar = name;
}

void Gui::SetStarClass(char Sclass)
{
    starClass[0] = Sclass;
}

void Gui::SetWindowOpen()
{
    windowOpen = true;
}
