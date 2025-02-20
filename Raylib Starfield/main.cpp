// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: main.cpp
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
#include "Window.h"
#include "Controls.h"	
#include "SceneManager.h"
#include "Title.h"
#include "Globals.h"
#include "StarSystem.h"
#include "ResourceManager.h"
#include "PlanetScene.h"

// --------------------------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// --------------------------------------------------------------------------------------------
void windowSize();

// --------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
// --------------------------------------------------------------------------------------------

bool exitGame_g = false;                                // Exit game flag
LoadedScene loadedScene = TITLE;                        // Current loaded scene
                                                        
SceneManager sceneManager;                              // SceneManager instance
SceneManager& sceneManager_ref = sceneManager;          // SceneManager reference
                                                        
Window window;                                          // Window instance
Camera& camera_ref = window.camera;                     // Camera reference
                                                        
Controls control;                                       // Controls instance
Controls& control_ref = control;                        // Controls reference
                                                        
Star* selectedStarPtr = nullptr;                           // Pointer to the selected star
                                                        
Gui* gui_ptr = nullptr;                                 // Gui reference
                                                        
Vector3 savedCameraPosition = {0.0f, 0.0f, 10.0f};      // Saved camera position for return space scene
Vector3 savedCameraTarget   = {0.0f, 0.0f, 0.0f};       // Saved camera rotation for return space scene

ResourceManager resourceManager;                        // Resource manager instance
ResourceManager& resourceManager_ref = resourceManager; // Resource manager reference

// --------------------------------------------------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------------------------------------------------
int main() 
{
    Gui gui;
	gui_ptr = &gui;

	//sceneManager.ChangeScene(new Title());
    sceneManager.ChangeScene(new Title());

    // Main game loop
    while (!exitGame_g) 
    {
        //if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) exitGame_g = true;

		windowSize();

        // --------------------------------------------------------------------------------------------
		// UPDATE - INPUT
		// --------------------------------------------------------------------------------------------
		control.Update();

		// --------------------------------------------------------------------------------------------
		// UPDATE - SCENE
		// --------------------------------------------------------------------------------------------
        sceneManager.currentScene->Update();

        // --------------------------------------------------------------------------------------------
		// DRAW - SCENE 
		// --------------------------------------------------------------------------------------------

        BeginDrawing(); 
        {
            ClearBackground(BLACK);

			
            
            BeginMode3D(window.camera);
            {
				// Draw the 3D scene
                sceneManager.currentScene->Draw3D();
            }
            EndMode3D();
            
            // Start 2D mode in front of the 3D image
            sceneManager.currentScene->Draw2D();
            gui_ptr->DrawInterface();
        }
        EndDrawing(); 
    }

    return 0;
}

// --------------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
// --------------------------------------------------------------------------------------------

// This function will check if the window has been resized and adjust the screen size accordingly
void windowSize()
{
    if (IsWindowResized() && !IsWindowFullscreen())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }
    // check for alt + enter
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
        // see what display we are on right now
        int display = GetCurrentMonitor();


        if (IsWindowFullscreen())
        {
            // if we are full screen, then go back to the windowed size
            SetWindowSize(screenWidth, screenHeight);
        }
        else
        {
            // if we are not full screen, set the window size to match the monitor we are on
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }

        // toggle the state
        ToggleFullscreen();
    }
}
