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

    void Init() override;
    void Update() override;
    void Draw2D() override;
    void Draw3D() override;
    void Unload() override;

    void Menu();

private:
    Scene* previousScene;
    std::vector<StarPixels> stars;
    int selectedOption = 0;
    const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    static constexpr const char* menuOptions[] = {"Start", "Options", "Exit"};
};

#endif // !H_TITLE_H
