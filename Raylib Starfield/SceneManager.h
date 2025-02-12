#ifndef H_SCENE_MANAGER_H
#define H_SCENE_MANAGER_H

#include "Scene.h"


class SceneManager {
public:
    Scene* currentScene = nullptr;

	// Change the current scene to a new scene and delete the old scene
    void ChangeScene(Scene* newScene) 
    {
        if (currentScene) {
            currentScene->Unload();
            delete currentScene;
        }
        currentScene = newScene;
        currentScene->Init();
    }
};

#endif // !H_SCENE_MANAGER_H



