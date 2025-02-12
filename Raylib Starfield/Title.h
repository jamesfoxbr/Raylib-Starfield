#ifndef H_TITLE_H
#define H_TITLE_H

#include <raylib.h>
#include <vector>
#include <cmath>
#include "Scene.h"
#include "Space.h" 
#include "SceneManager.h"
#include "Globals.h"

struct StarPixels {
    float x, y, z;
};

class Title : public Scene
{
public:
    Title();
    ~Title();

    void Init() override;    // Called when the scene is loaded
    void Update() override;  // Called every frame
    void Draw2D() override;  // Called every frame to draw 2D elements
    void Draw3D() override;  // Called every frame to draw 3D elements
    void Unload() override;  // Called when the scene is unloaded

    void Menu();

private:
    Scene* previousScene;
    std::vector<StarPixels> stars;
    int selectedOption = 0;
    const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    static constexpr const char* menuOptions[] = {"Start", "Options", "Exit"};
};

#endif // !H_TITLE_H
