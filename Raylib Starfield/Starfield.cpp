#include "Starfield.h"

Starfield::Starfield(const int starCount, const int starDrawDistance, const int chunkSize)
    :
    stars(starCount), 
    starDrawDistance(starDrawDistance),
	size(chunkSize)
{
    InitializeStars(starCount, starDrawDistance, chunkSize);
}

Starfield::Starfield(const int starCount, const int starDrawDistance, Vector3 position, const int chunkSize)
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

const void Starfield::InitializeStars(const int starCount, const int starDrawDistance, const int chunkSize)
{
    // Randomly initialize the stars
    std::srand(static_cast<unsigned int>(std::time(0)));
    for (int i = 0; i < starCount; ++i) 
    {
        stars[i].SetPosition({static_cast<float>((std::rand() % (size))) + position.x,    // x
                              static_cast<float>((std::rand() % (size))) + position.y,    // y
                              static_cast<float>((std::rand() % (size))) + position.z});  // z
        stars[i].SetName("Star " + std::to_string(i)); // Assign a name for each star
    }
}

const void Starfield::DrawStars(const Camera& camera) const
{
    RLFrustum rlFrustum; // Create an instance of RLFrustum

    for (auto& star : stars) {
        // Draw visible stars
        float scale = 0.1f;

        if (distance(camera.position, star.GetPosition()) > starDrawDistance)
        {
            DrawPoint3D(star.GetPosition(), star.GetColor());
        }
        else
        {
           
            if (rlFrustum.SphereIn(star.GetPosition(), scale))
            {
                DrawSphereEx(star.GetPosition(), scale, 4, 5, star.GetColor());
            }
        }
    }

    //const Vector3 cubePosition = {position.x + size / 2, position.y + size / 2, position.z + size / 2};

    //DrawCubeWires(cubePosition, (float)size, (float)size, (float)size, WHITE); // starfield area
}

const Vector3 Starfield::GetPosition() const
{
    return position;
}
