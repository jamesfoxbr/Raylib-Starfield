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

    // ---------- EXIT CONFIRMATION ---------- //
    if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    {
        ImGui::OpenPopup("Exit Confirmation");
    }

    ImGui::SetNextWindowPos(ImVec2((GetScreenWidth() - 300) / 2, (GetScreenHeight() - 100) / 2), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

    if (ImGui::BeginPopupModal("Exit Confirmation", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure you want to exit the game?");
        if (ImGui::Button("Yes", ImVec2(120, 0)))
        {
            exitGame_g = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
   
    switch (loadedScene)
    {
		// ---------- TITLE ---------- //
    case TITLE:
    {
        // ---------- SELECTION MENU ---------- //
        const float windowWidth  = 200;
        const float windowHeight = 200;
		const float buttonHeight = 20;
       
        ImGui::SetNextWindowSize({windowWidth, windowHeight});
        ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowWidth / 2, (GetScreenHeight() / 2) - windowHeight / 2});

        ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		
        if (ImGui::Button("START", {windowWidth - 16, buttonHeight}))
        {
            // Start game (Space scene)
            loadedScene = SPACE;
            sceneManager_ref.ChangeScene(new Space());
        }
        if (ImGui::Button("OPTION", {windowWidth - 16, buttonHeight}))
        {
            // Handle OPTION button click
        }
        if (ImGui::Button("EXIT", {windowWidth - 16, buttonHeight}))
        {
            // Handle EXIT button click
            exitGame_g = true;
        }
        ImGui::End();
    }
        break;

		// ---------- SPACE ---------- //
    case SPACE:
    {
        // ---------- COORDINATES INFORMATION ---------- //
        // Coordinates window
        const float windowWidth = 200;

        ImGui::SetNextWindowSize({400, 72});
        ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowWidth, 4});
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
            const float windowWidth = 200;
            const float windowHeight = 200;
            const float buttonHeight = 20;

            ImGui::SetNextWindowSize({windowWidth, windowHeight});
            ImGui::SetNextWindowPos({GetScreenWidth() - windowWidth, 0});

            ImGui::SetWindowSize({200, 100});
            ImGui::Begin("STAR INFORMATION", &windowOpen, ImGuiWindowFlags_NoResize);
            ImGui::Text(("Star Name: " + selectedStar).c_str());

            char s[23] = "Star Spectral Class: ";
            s[21] = *starClass;
            ImGui::Text(s);

            if (ImGui::Button("ENTER", {windowWidth - 16, buttonHeight}) && !selectedStar.empty())
            {
                // Start game (Space scene)
                loadedScene = STARSYSTEM;
                sceneManager_ref.ChangeScene(new StarSystem());
            }

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

		// ---------- STARSYSTEM ---------- //
    case STARSYSTEM:
    {
        const float windowWidth = 200;
        const float windowHeight = 200;
        const float buttonHeight = 20;

        ImGui::SetNextWindowSize({windowWidth, windowHeight});
        ImGui::SetNextWindowPos({GetScreenWidth() - windowWidth, 0});

        ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        if (ImGui::Button("RETURN", {windowWidth - 16, buttonHeight}))
        {
            // Start game (Space scene)
            loadedScene = SPACE;
            sceneManager_ref.ChangeScene(new Space());
        }
        ImGui::End();
    }
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


