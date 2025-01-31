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
		stars[i].SetName(GenerateName(size_t(random() % 7 + 1), random)); // Generate a random name for each star
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

std::string Starfield::GenerateName(size_t length, std::mt19937& rng)
{
    std::string name;
    std::uniform_int_distribution<> distConsonants(0, int(consonants.size() - 1));
    std::uniform_int_distribution<> distVowels(0, int(vowels.size() - 1));
    for (size_t i = 0; i < length; ++i)
    {
        name += consonants[distConsonants(rng)];
        name += vowels[distVowels(rng)];
    }
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    return name;
}