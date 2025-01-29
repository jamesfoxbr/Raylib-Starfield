#include "Starfield.h"

Starfield::Starfield(const int starCount, const int starDrawDistance, Vector3 position, const int chunkSize, std::mt19937& random)
    :
    stars(starCount),
    starDrawDistance(starDrawDistance),
    size(chunkSize)
{
    this->position.x = position.x * chunkSize;
    this->position.y = position.y * chunkSize;
    this->position.z = position.z * chunkSize;

    InitializeStars(starCount, starDrawDistance, chunkSize, random);
}

Starfield::~Starfield()
{
}

const void Starfield::InitializeStars(const int starCount, const int starDrawDistance, const int chunkSize, std::mt19937& random)
{
    // Randomly initialize the stars
	random.seed(unsigned int(position.x + position.y + position.x));
    for (int i = 0; i < starCount; ++i) 
    {
        stars[i].SetPosition({random() % (size)+position.x,    // x
                              random() % (size)+position.y,    // y
                              random() % (size)+position.z});  // z

        stars[i].SetName("Star " + std::to_string(i));         // Assign a name for each star
		stars[i].SpectralClass(random() % 100);                // Assign a spectral class for each star

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

bool Starfield::IsStarClicked(Camera& camera) const
{
    for (auto& star : stars)
    {
        Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera);
        const float starSize = 20.0f;      // Use the star's size for collision detection
		const float clickDistance = 100.0f; // How far the mouse can be from the star to click it
        if (CheckCollisionPointCircle({screenWidth / 2, screenHeight / 2}, screenPos, starSize) && distance(star.GetPosition(), camera.position) < clickDistance)
        {
			DrawCube(star.GetPosition(), 1.0f, 1.0f, 1.0f, RED);
            return true;
        }
    }
    return false;
}