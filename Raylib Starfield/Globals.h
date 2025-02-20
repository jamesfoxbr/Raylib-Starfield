// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Globals.H
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

#ifndef H_GLOBALS_H
#define H_GLOBALS_H

#include <raylib.h>
#include "SceneManager.h"
#include "Controls.h"
#include "Gui.h"
#include "Star.h" 
#include "ResourceManager.h"

enum LoadedScene
{
    TITLE,
    SPACE,
    STARSYSTEM,
    PLANET
};

static int screenWidth = 1280; 
static int screenHeight = 800;

static const int SEED = 555;

extern Vector3 savedCameraPosition;          // Saved camera position for return space scene
extern Vector3 savedCameraTarget;            // Saved camera rotation for return space scene
                                             
extern SceneManager& sceneManager_ref;       // Reference to the scene manager
extern Camera& camera_ref;                   // Reference to the camera
extern ResourceManager& resourceManager_ref; // Reference to the resource manager

extern Controls& control_ref;                // Reference to the controls
extern Gui* gui_ptr;                         // Pointer to the GUI
                                            
extern Star* selectedStarPtr;                   // Pointer to the selected star
                                            
extern bool exitGame_g;                      // Exit game flag
extern LoadedScene loadedScene;              // Current loaded scene

#endif // !H_GLOBALS_H
