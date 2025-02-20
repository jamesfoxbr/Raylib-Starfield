// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Gui.cpp
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

#include "Gui.h"
#include "Globals.h"
#include "Space.h"
#include "StarSystem.h"
#include "Title.h"
#include "ResourceManager.h"

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
    rlImGuiBegin();

    #ifdef _DEBUG
    DebugInterface();
    #else
    #endif

    SetExitConfirmationOpen();
	
    switch (loadedScene)
    {
    case TITLE:
    {
        TitleInterface();
    }
        break;
    case SPACE:
    {
        SpaceInterface();
    }
        break;
    case STARSYSTEM:
    {
        StarSystemInterface();
    }
        break;
    default:

        break;
    }

    rlImGuiEnd();
}

void Gui::DebugInterface()
{
    ImGui::Begin("DEBUG INFORMATION");
    ImGui::Text(("FPS: " + std::to_string(GetFPS())).c_str());

    if (loadedScene == SPACE)
    {
        ImGui::Text(("STARS: " + std::to_string(sceneManager_ref.currentScene->GetNumberOfStars())).c_str());
    }

    ImGui::End();
}

void Gui::TitleInterface()
{
    // ---------- SELECTION MENU ---------- //
    const float windowWidth = 200;
    const float windowHeight = 200;
    const float buttonHeight = 20;

    ImGui::SetNextWindowSize({windowWidth, windowHeight});
    ImGui::SetNextWindowPos({(GetScreenWidth() / 2) - windowWidth / 2, (GetScreenHeight() / 2) - windowHeight / 2});

    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (ImGui::Button("START", {windowWidth - 16, buttonHeight}))
    {
        // Start game (Space scene)
        sceneManager_ref.ChangeScene(new Space());
    }
    if (ImGui::Button("OPTION", {windowWidth - 16, buttonHeight}))
    {
        // Handle OPTION button click
    }
    if (ImGui::Button("EXIT", {windowWidth - 16, buttonHeight}))
    {
        // Handle EXIT button click
        exitConfirmation = true;
    }
    ImGui::End();
}

void Gui::SpaceInterface()
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

    // ---------- STAR INFORMATION GUI ---------- //
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
            savedCameraPosition = camera_ref.position;
            savedCameraTarget = camera_ref.target;
            sceneManager_ref.ChangeScene(new StarSystem(selectedStarPtr->GetName(), selectedStarPtr->GetPosition()));
        }

        ImGui::End();
    }
}

void Gui::StarSystemInterface()
{
    const float windowWidth = 300;
    const float windowHeight = 200;
    const float buttonHeight = 20;

    ImGui::SetNextWindowSize({windowWidth, windowHeight});
    ImGui::SetNextWindowPos({GetScreenWidth() - windowWidth, 0});

    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Text(("Star Name: " + selectedStar).c_str());
    ImGui::Text(("World Type: " + sceneManager_ref.currentScene->GetWorldType()).c_str());
    ImGui::Text(("Atmospheric Pressure: " + std::to_string(sceneManager_ref.currentScene->GetAtmosphericPressure())).c_str());

    if (ImGui::Button("RETURN", {windowWidth - 16, buttonHeight}))
    {
        sceneManager_ref.ChangeScene(new Space());
    }
    ImGui::End();
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

void Gui::SetExitConfirmationOpen()
{
    // ---------- EXIT CONFIRMATION ---------- //
	if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose() || exitConfirmation)
    {
        ImGui::OpenPopup("Exit Confirmation");
    }

    ImGui::SetNextWindowPos(ImVec2((GetScreenWidth() - 300.0f) / 2.0f, (GetScreenHeight() - 100.0f) / 2.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

    if (ImGui::BeginPopupModal("Exit Confirmation", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure you want to exit the game?");
        if (ImGui::Button("Yes", ImVec2(120, 0)))
        {
            exitGame_g = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine(15.0f, 155.0f);
        if (ImGui::Button("No", ImVec2(120, 0)))
        {
			exitConfirmation = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void Gui::ReturnToTitle()
{
    // ---------- EXIT CONFIRMATION ---------- //
    if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())
    {
        ImGui::OpenPopup("Return to title");
    }

    ImGui::SetNextWindowPos(ImVec2((GetScreenWidth() - 300.0f) / 2.0f, (GetScreenHeight() - 100.0f) / 2.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_Always);

    if (ImGui::BeginPopupModal("Return to title", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure you want return to title?");
        if (ImGui::Button("Yes", ImVec2(120, 0)))
        {
			sceneManager_ref.ChangeScene(new Title());
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine(15.0f, 155.0f);
        if (ImGui::Button("No", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}