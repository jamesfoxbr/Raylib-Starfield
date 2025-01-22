#include "Starfield.h"

double distance(Vector3 p1, Vector3 p2)
{
    double d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2) * 1.0);
    return d;
}

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
        stars[i].position = {static_cast<float>((std::rand() % (width * 2)) - width),   // x
                             static_cast<float>((std::rand() % (height * 2)) - height),  // y
                             static_cast<float>((std::rand() % (depth * 2)) - depth)};  // z
        stars[i].color = Color(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255);
        stars[i].name = "Star " + std::to_string(i); // Assign a name for each star
    }
}

void Starfield::DrawStars(Camera& camera)
{
    for (const auto& star : stars) {

        // Draw visible stars
        float scale = 0.02f - (star.position.z / 1000.0f);

        if (distance(camera.position, star.position) > 50.0f)
        {
            DrawPoint3D(star.position, star.color);
        }
        else
        {
            DrawSphereEx(star.position, scale, 4, 5, star.color);
        }
    }
}
