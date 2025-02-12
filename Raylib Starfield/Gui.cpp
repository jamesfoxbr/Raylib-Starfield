#include "Gui.h"
#include "Globals.h"
#include "Space.h"

Gui::Gui()
{
    // sets up ImGui with ether a dark or light default theme
    rlImGuiSetup(true);
}

Gui::~Gui()
{
    // cleans up ImGui
    rlImGuiShutdown();	
}

void Gui::DrawInterface()
{
    // starts the ImGui content mode. Make all ImGui calls after this
    rlImGuiBegin();

    #ifdef _DEBUG

    // ---------- DEBUG INFORMATION ---------- //
    ImGui::Begin("DEBUG INFORMATION");
    ImGui::Text(("FPS: " + std::to_string(GetFPS())).c_str());
    ImGui::End();

    #else
        
    #endif
   
    switch (loadedScene)
    {
    case TITLE:
    {
        const float windowWidth  = 200;
        const float windowHeight = 200;
        // ---------- SELECTION MENU ---------- //
        ImGui::SetNextWindowSize({windowWidth, windowHeight});
        ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowWidth / 2, (GetScreenHeight() / 2) - windowHeight / 2});

        ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		
        if (ImGui::Button("START", {windowWidth - 16, 20}))
        {
            // Start game (Space scene)
            loadedScene = SPACE;
            sceneManager_ref.ChangeScene(new Space());
        }
        if (ImGui::Button("OPTION", {windowWidth - 16, 20}))
        {
            // Handle OPTION button click
        }
        if (ImGui::Button("EXIT", {windowWidth - 16, 20}))
        {
            // Handle EXIT button click
            exitGame_g = true;
        }
        ImGui::End();
    }
        break;
    case SPACE:
    {
        // ---------- COORDINATES INFORMATION ---------- //
        // Coordinates window
        float windowSize = 200;

        ImGui::SetNextWindowSize({400, 72});
        ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowSize, 4});
        ImGui::Begin("COORDINATES", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::Text(("Coordinates: X " + std::to_string((int)camera_ref.position.x) +
            " / Y " + std::to_string((int)camera_ref.position.y)
            + " / Z " + std::to_string((int)camera_ref.position.z)).c_str());

        int coordinates[3] = {(int)camera_ref.position.x, (int)camera_ref.position.y, (int)camera_ref.position.z};
        if (ImGui::InputInt3("Input Coordinates", coordinates))
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
            {
                camera_ref.position.x = (float)coordinates[0];
                camera_ref.position.y = (float)coordinates[1];
                camera_ref.position.z = (float)coordinates[2];
                camera_ref.target = Vector3{0.0f, 0.0f, 0.0f};
            }

        ImGui::End();

        // ---------- STAR INFORMATION ---------- //
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

        
    }
        break;
    case STARSYSTEM:

        break;
    default:

        break;
    }
    		
    // ends the ImGui content mode. Make all ImGui calls before this
    rlImGuiEnd();
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
