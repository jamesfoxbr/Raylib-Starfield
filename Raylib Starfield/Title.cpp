// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Title.cpp
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

#include "Title.h"
#include "Globals.h"

Title::Title()
{
	loadedScene = TITLE; // Set the loaded scene to TITLE
}

Title::~Title()
{
}

void Title::Init()
{
	// Initialize stars in the background for the title screen
    const int numStars = 1000;
    stars.resize(numStars);
    for (auto& star : stars) {
        star.x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 2, GetScreenWidth() / 2));
        star.y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 2, GetScreenHeight() / 2));
        star.z = static_cast<float>(GetRandomValue(1, GetScreenWidth()));
    }
}

void Title::Update()
{
	// Update stars in the background for the title screen
    for (auto& star : stars) {
        star.z -= 10;
        if (star.z <= 0) {
            star.x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 2, GetScreenWidth() / 2));
            star.y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 2, GetScreenHeight() / 2));
            star.z = static_cast<float>(GetScreenWidth());
        }
    }

	// Menu navigation 
   // if (IsKeyPressed(KEY_DOWN)) 
   // {
   //     selectedOption = (selectedOption + 1) % menuOptionsCount;
   // }
   // if (IsKeyPressed(KEY_UP)) 
   // {
   //     selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
   // }
   // if (IsKeyPressed(KEY_ENTER)) 
   // {
   //     switch (selectedOption) 
   //     {
   //     case 0:
			//// Start game (Space scene)
			//loadedScene = SPACE;
   //         sceneManager_ref.ChangeScene(new Space());
   //         break;
   //     case 1:
			//// Options (not implemented)
   //         break;
   //     case 2:
			//// Exit game
			//exitGame_g = true;
   //         break;
   //     }
   // }
}

void Title::Draw2D()
{
	// Draw stars in the background for the title screen
    for (const auto& star : stars) {
        float sx = star.x / star.z * GetScreenWidth() / 2 + GetScreenWidth() / 2;
        float sy = star.y / star.z * GetScreenHeight() / 2 + GetScreenHeight() / 2;
        float brightness = .0f - star.z / GetScreenWidth();
        Color color = { 255, 255, 255, static_cast<unsigned char>(brightness * 255) };
        DrawPixel(static_cast<int>(sx), static_cast<int>(sy), color);
    }

	// Draw title screen text
    DrawText("GALAXY MAP", 50, 50, 50, WHITE);
    DrawLine(50, 100, GetScreenWidth() - 50, 100, WHITE);
    DrawText("TESSERACT UNIVERSE", 50, 110, 20, WHITE);
    DrawText("By Jamesfoxbr", GetScreenWidth() - 200, 110, 20, WHITE);

	// Draw menu options on the title screen
   /* for (int i = 0; i < menuOptionsCount; i++) {
        Color color = (i == selectedOption) ? YELLOW : WHITE;
        DrawText(menuOptions[i], GetScreenWidth() / 2 - MeasureText(menuOptions[i], 20) / 2, GetScreenHeight() / 2 + i * 30, 20, color);
    }*/
}

void Title::Menu()
{

}

void Title::Draw3D()
{
}

void Title::Unload()
{
	// Clear stars in the background for the title screen before unloading
    stars.clear();
}
