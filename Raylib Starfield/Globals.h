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
    STARSYSTEM
};

static int screenWidth = 900; 
static int screenHeight = 600;

extern Vector3 savedCameraPosition;          // Saved camera position for return space scene
extern Vector3 savedCameraTarget;            // Saved camera rotation for return space scene
                                             
extern SceneManager& sceneManager_ref;       // Reference to the scene manager
extern Camera& camera_ref;                   // Reference to the camera
extern ResourceManager& resourceManager_ref; // Reference to the resource manager

extern Controls& control_ref;                // Reference to the controls
extern Gui* gui_ptr;                         // Pointer to the GUI
                                            
extern Star* selectedStar;                   // Pointer to the selected star
                                            
extern bool exitGame_g;                      // Exit game flag
extern LoadedScene loadedScene;              // Current loaded scene

#endif // !H_GLOBALS_H
