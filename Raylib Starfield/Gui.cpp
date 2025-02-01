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

Color Gui::GetClearColor()
{
	return Color{(unsigned char)(clear_color.x * 255), (unsigned char)(clear_color.y * 255), (unsigned char)(clear_color.z * 255), (unsigned char)(clear_color.w * 255)};
}

void Gui::DrawInterface()
{
    rlImGuiBegin();			// starts the ImGui content mode. Make all ImGui calls after this
    
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("COORDINATES");  // Create a window called "STAR INFORMATION" and append into it.
    ImGui::Text(("Coordinates: X " + std::to_string((int)camera.position.x) +
        " / Y " + std::to_string((int)camera.position.y)
        + " / Z " + std::to_string((int)camera.position.z)).c_str());
    ImGui::End();

    if (windowOpen)
    {
        ImGui::Begin("STAR INFORMATION", &windowOpen);  // Create a window called "STAR INFORMATION" and append into it.
        
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
