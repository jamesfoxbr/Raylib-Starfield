#include "Starfield.h"

Starfield::Starfield(const int starCount, const int starDrawDistance, Vector3 position, const int chunkSize, std::mt19937& random)
    :
    stars(starCount),
    size(chunkSize)
{
    this->position.x = position.x * chunkSize;
    this->position.y = position.y * chunkSize;
    this->position.z = position.z * chunkSize;

    InitializeStars(starCount, starDrawDistance, chunkSize, random);

    std::cout << "starfield Constructed \n";
}

Starfield::~Starfield()
{
    std::cout << "starfield destroyed \n";
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
		stars[i].SetName(GenerateName(size_t(random() % 10 + 5), random)); // Generate a random name for each star
		stars[i].SpectralClass(random() % 100);                // Assign a spectral class for each star

		numberOfStars = i;
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

Star* Starfield::IsStarClicked(Camera& camera) const
{
    for (auto& star : stars)
    {
        Vector2 screenPos = GetWorldToScreen(star.GetPosition(), camera);
        const float starSize      = 20.0f;  // Use the star's size for collision detection
        const float clickDistance = 100.0f; // How far the mouse can be from the star to click it

        if (CheckCollisionPointCircle({screenWidth / 2, screenHeight / 2}, screenPos, starSize) && distance(star.GetPosition(), camera.position) < clickDistance)
        {
            DrawCube(star.GetPosition(), 1.0f, 1.0f, 1.0f, RED);
            return const_cast<Star*>(&star);
        }
    }
    return nullptr;
}

std::string Starfield::GenerateName(size_t length, std::mt19937& rng)
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	const std::string vowels = "aeiouy";

    std::string name;
    std::uniform_int_distribution<> distAlphabet(0, int(alphabet.size() - 1));
    std::uniform_int_distribution<> distSylVow(0, int(vowels.size() - 1));
    for (size_t i = 0; i < length; ++i) 
    {
        name += alphabet[distAlphabet(rng)];
		if (rng() % 100 < 10)
		name += vowels[distSylVow(rng)];
    }
    return name;
}