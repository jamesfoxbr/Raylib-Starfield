#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Init()
{
    const int numStars = 1000;
    stars.resize(numStars);
    for (auto& star : stars) {
        star.x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 2, GetScreenWidth() / 2));
        star.y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 2, GetScreenHeight() / 2));
        star.z = static_cast<float>(GetRandomValue(1, GetScreenWidth()));
    }
}

void Title::Update()
{
    for (auto& star : stars) {
        star.z -= 10;
        if (star.z <= 0) {
            star.x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 2, GetScreenWidth() / 2));
            star.y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 2, GetScreenHeight() / 2));
            star.z = static_cast<float>(GetScreenWidth());
        }
    }

    if (IsKeyPressed(KEY_DOWN)) 
    {
        selectedOption = (selectedOption + 1) % menuOptionsCount;
    }
    if (IsKeyPressed(KEY_UP)) 
    {
        selectedOption = (selectedOption - 1 + menuOptionsCount) % menuOptionsCount;
    }
    if (IsKeyPressed(KEY_ENTER)) 
    {
        switch (selectedOption) 
        {
        case 0:
            // Start game
			loadedScene = SPACE;
            sceneManager_ref.ChangeScene(new Space());
            break;
        case 1:
            // Options
            break;
        case 2:
            // Exit
			exitGame_g = true;
            break;
        }
    }
}

void Title::Draw2D()
{
    for (const auto& star : stars) {
        float sx = star.x / star.z * GetScreenWidth() / 2 + GetScreenWidth() / 2;
        float sy = star.y / star.z * GetScreenHeight() / 2 + GetScreenHeight() / 2;
        float brightness = .0f - star.z / GetScreenWidth();
        Color color = { 255, 255, 255, static_cast<unsigned char>(brightness * 255) };
        DrawPixel(static_cast<int>(sx), static_cast<int>(sy), color);
    }

    DrawText("GALAXY MAP", 50, 50, 50, WHITE);
    DrawLine(50, 100, GetScreenWidth() - 50, 100, WHITE);
    DrawText("TESSERACT UNIVERSE", 50, 110, 20, WHITE);
    DrawText("By Jamesfoxbr", GetScreenWidth() - 200, 110, 20, WHITE);

    for (int i = 0; i < menuOptionsCount; i++) {
        Color color = (i == selectedOption) ? YELLOW : WHITE;
        DrawText(menuOptions[i], GetScreenWidth() / 2 - MeasureText(menuOptions[i], 20) / 2, GetScreenHeight() / 2 + i * 30, 20, color);
    }
}

void Title::Menu()
{

}

void Title::Draw3D()
{
}

void Title::Unload()
{
    stars.clear();
}
