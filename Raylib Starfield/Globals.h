#ifndef H_GLOBALS_H
#define H_GLOBALS_H

#include <raylib.h>
#include "SceneManager.h"

enum LoadedScene
{
	TITLE,
	SPACE,
	STARSYSTEM
};
static int screenWidth = 900;
static int screenHeight = 600;

extern SceneManager& sceneManager_ref;
extern Camera& camera_ref;

extern bool exitGame_g;
extern LoadedScene loadedScene;

#endif // !H_GLOBALS_H



