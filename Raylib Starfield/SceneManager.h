#ifndef H_SCENE_MANAGER_H
#define H_SCENE_MANAGER_H

#include "Scene.h"


class SceneManager {
public:
    static Scene* currentScene;

    static void ChangeScene(Scene* newScene) {
        if (currentScene) {
            currentScene->Unload();
            delete currentScene;
        }
        currentScene = newScene;
        currentScene->Init();
    }
};

Scene* SceneManager::currentScene = nullptr; // Initialize to nullptr


#endif // !H_SCENE_MANAGER_H



