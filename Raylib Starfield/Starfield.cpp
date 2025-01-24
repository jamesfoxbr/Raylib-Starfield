#include "Starfield.h"

Starfield::Starfield(int starCount, int starDrawDistance, int width, int height, int depth)
    :
    stars(starCount), 
    starDrawDistance(starDrawDistance),
    width(width),
    height(height),
    depth(depth)
{
    InitializeStars(starCount, starDrawDistance, width, height, depth);
}

Starfield::Starfield(int starCount, int starDrawDistance)
    :
    stars(starCount),
    starDrawDistance(starDrawDistance)
{
    InitializeStars(starCount, starDrawDistance, 100, 100, 100);
}

Starfield::~Starfield()
{
}

void Starfield::InitializeStars(int starCount, int starDrawDistance, int width, int height, int depth)
{
    // Randomly initialize the stars
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < starCount; ++i) {
        stars[i].SetPosition({static_cast<float>((std::rand() % (width * 2)) - width),   // x
                             static_cast<float>((std::rand() % (height * 2)) - height),  // y
                             static_cast<float>((std::rand() % (depth * 2)) - depth)});  // z
        stars[i].SetColor(Color(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255));
        stars[i].SetName("Star " + std::to_string(i)); // Assign a name for each star
    }
}

void Starfield::DrawStars(Camera& camera)
{

    for (auto& star : stars) {

        // Draw visible stars
        float scale = 0.02f;

        if (distance(camera.position, star.GetPosition()) > 50.0f)
        {
            DrawPoint3D(star.GetPosition(), star.GetColor());
        }
        else
        {
            DrawSphereEx(star.GetPosition(), scale, 4, 5, star.GetColor());
        }
    }
}
