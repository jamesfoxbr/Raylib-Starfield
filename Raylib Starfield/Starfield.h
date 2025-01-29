#ifndef H_STARFIELD
#define H_STARFIELD

#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <vector>
#include "Star.h"
#include "Utils.h"

class Starfield
{
public:
	Starfield(const int starCount, const int starDrawDistance, const Vector3 position, const int chunkSize, std::mt19937& random);
	~Starfield();
	const void InitializeStars(const int starCount, const int starDrawDistance, const int size, std::mt19937& random);
	const void DrawStars(const Camera& camera) const;
	const Vector3 GetPosition() const;
	const int GetNumberOfStars() const;

	bool IsStarClicked(Camera& camera) const;

private:
	Vector3 position = {0.0f, 0.0f, 0.0f};
	std::vector<Star> stars;
	int starDrawDistance = 100;
	int size;
	int numberOfStars = 0;
};

#endif // !H_STARFIELD



