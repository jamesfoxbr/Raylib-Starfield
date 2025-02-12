#ifndef H_GLOBALS_H
#define H_GLOBALS_H

#include <raylib.h>
#include "SceneManager.h"
#include "Controls.h"

enum LoadedScene
{
	TITLE,
	SPACE,
	STARSYSTEM
};
static int screenWidth = 900; 
static int screenHeight = 600;

extern SceneManager& sceneManager_ref; // Reference to the scene manager
extern Camera& camera_ref;             // Reference to the camera
extern Controls& control_ref;          // Reference to the controls

extern bool exitGame_g;				   // Exit game flag
extern LoadedScene loadedScene;		   // Current loaded scene

#endif // !H_GLOBALS_H



