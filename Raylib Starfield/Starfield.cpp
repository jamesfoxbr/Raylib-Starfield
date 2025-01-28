#include "Starfield.h"

Starfield::Starfield(int starCount, int starDrawDistance, int size)
    :
    stars(starCount), 
    starDrawDistance(starDrawDistance)
{
    InitializeStars(starCount, starDrawDistance, size);
}

Starfield::Starfield(int starCount, int starDrawDistance, Vector3 position)
    :
    stars(starCount),
    starDrawDistance(starDrawDistance)
{
    this->position.x = position.x * 100;
    this->position.y = position.y * 100;
    this->position.z = position.z * 100;

    InitializeStars(starCount, starDrawDistance, 100);
}

Starfield::~Starfield()
{
}

void Starfield::InitializeStars(int starCount, int starDrawDistance, int size)
{
    // Randomly initialize the stars
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < starCount; ++i) {
        stars[i].SetPosition({static_cast<float>((std::rand() % (size)))  + position.x,    // x
                              static_cast<float>((std::rand() % (size))) + position.y,    // y
                              static_cast<float>((std::rand() % (size)))  + position.z});  // z
        stars[i].SetName("Star " + std::to_string(i)); // Assign a name for each star
    }
}

void Starfield::DrawStars(Camera& camera)
{

    for (auto& star : stars) {

        // Draw visible stars
        float scale = 0.1f;

        if (distance(camera.position, star.GetPosition()) > 50.0f)
        {
            DrawPoint3D(star.GetPosition(), star.GetColor());
        }
        else
        {
            DrawSphereEx(star.GetPosition(), scale, 4, 5, star.GetColor());
        }
    }

    const Vector3 cubePosition = {position.x + size / 2, position.y + size / 2, position.z + size / 2};

    DrawCubeWires(cubePosition, (float)size, (float)size, (float)size, WHITE);
}

Vector3 Starfield::GetPosition()
{
    return position;
}
