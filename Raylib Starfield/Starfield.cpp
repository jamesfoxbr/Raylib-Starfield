#include "Starfield.h"

Starfield::Starfield(int starCount, int starDrawDistance, int chunkSize)
    :
    stars(starCount), 
    starDrawDistance(starDrawDistance),
	size(chunkSize)
{
    InitializeStars(starCount, starDrawDistance, chunkSize);
}

Starfield::Starfield(int starCount, int starDrawDistance, Vector3 position, int chunkSize)
    :
    stars(starCount),
    starDrawDistance(starDrawDistance),
    size(chunkSize)
{
    this->position.x = position.x * chunkSize;
    this->position.y = position.y * chunkSize;
    this->position.z = position.z * chunkSize;

    InitializeStars(starCount, starDrawDistance, chunkSize);
}

Starfield::~Starfield()
{
}

const void Starfield::InitializeStars(int starCount, int starDrawDistance, int chunkSize)
{
    // Randomly initialize the stars
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < starCount; ++i) {
        stars[i].SetPosition({static_cast<float>((std::rand() % (size))) + position.x,    // x
                              static_cast<float>((std::rand() % (size))) + position.y,    // y
                              static_cast<float>((std::rand() % (size))) + position.z});  // z
        stars[i].SetName("Star " + std::to_string(i)); // Assign a name for each star
    }
}

const void Starfield::DrawStars(Camera& camera)
{

    for (const auto& star : stars) {

        // Draw visible stars
        constexpr float scale = 0.1f;

        if (distance(camera.position, star.GetPosition()) > starDrawDistance)
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

const Vector3 Starfield::GetPosition()
{
    return position;
}
