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

		numberOfStars = i;
    }
}

const void Starfield::DrawStars(const Camera& camera) const
{
    Vector3 cameraForward = Vector3Subtract(camera.target, camera.position);
    cameraForward = Vector3Normalize(cameraForward); // Get forward direction

    for (auto& star : stars) {
        Vector3 toStar = Vector3Subtract(star.GetPosition(), camera.position);
        float dotProduct = Vector3DotProduct(cameraForward, toStar);

        // Check if the star is in front of the camera
        if (dotProduct <= 0) continue; // Skip stars behind the camera

        float scale = 0.1f;
        if (distance(camera.position, star.GetPosition()) > starDrawDistance)
        {
            DrawPoint3D(star.GetPosition(), star.GetColor());
        }
        else
        {
            if (scale < 0.1f) 
            {
                scale = 0.1f;
            }

            DrawSphereEx(star.GetPosition(), scale, 4, 5, star.GetColor());
        }
    }
}


const Vector3 Starfield::GetPosition() const
{
    return position;
}

const int Starfield::GetNumberOfStars() const
{
    return numberOfStars;
}
