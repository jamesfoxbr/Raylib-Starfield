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
	Starfield(const int starCount, const int starDrawDistance, const int chunkSize);
	Starfield(const int starCount, const int starDrawDistance, const Vector3 position, const int chunkSize);
	~Starfield();
	const void InitializeStars(const int starCount, const int starDrawDistance, const int size);
	const void DrawStars(const Camera& camera) const;
	bool IsPointInFrontOfCamera(const Vector3& camPos, const Vector3& camForward, const Vector3& point) const;
	const Vector3 GetPosition() const;
	const int GetNumberOfStars() const;

private:
	Vector3 position = {0.0f, 0.0f, 0.0f};
	std::vector<Star> stars;
	int starDrawDistance = 100;
	int size;
	int numberOfStars = 0;
};

#endif // !H_STARFIELD



