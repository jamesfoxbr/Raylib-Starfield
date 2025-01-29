#ifndef H_STARFIELD
#define H_STARFIELD

#include "raylib.h"
#include <ctime>
#include <vector>
#include "Star.h"
#include "Utils.h"
#include "rlFrustum.h"

class Starfield
{
public:
	Starfield(int starCount, int starDrawDistance, int chunkSize);
	Starfield(int starCount, int starDrawDistance, Vector3 position, int chunkSize);
	~Starfield();
	const void InitializeStars(int starCount, int starDrawDistance, int size);
	const void DrawStars(const Camera& camera) const;
	const Vector3 GetPosition();

private:
	Vector3 position = {0.0f, 0.0f, 0.0f};
	std::vector<Star> stars;
	int starDrawDistance = 100;
	int size;
};

#endif // !H_STARFIELD



