#ifndef H_GLOBALS_H
#define H_GLOBALS_H

enum LoadedScene
{
	TITLE,
	SPACE,
	STARSYSTEM
};
static int screenWidth = 900;
static int screenHeight = 600;

extern bool global_exitGame;
extern LoadedScene loadedScene;

#endif // !H_GLOBALS_H



