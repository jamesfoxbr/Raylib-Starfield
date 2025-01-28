#ifndef H_STARFIELD
#define H_STARFIELD

#include "raylib.h"
#include <ctime>
#include <vector>
#include "Star.h"
#include "Utils.h"

class Starfield
{
public:
	Starfield(int starCount, int starDrawDistance, int width, int height, int depth);
	Starfield(int starCount, int starDrawDistance, Vector3 position);
	~Starfield();
	void InitializeStars(int starCount, int starDrawDistance, int width, int height, int depth);
	void DrawStars(Camera& camera);

private:
	Vector3 position = {0.0f, 0.0f, 0.0f};
	std::vector<Star> stars;
	int starDrawDistance = 100;
	int width = 100;
	int height = 100;
	int depth = 100;
};

#endif // !H_STARFIELD



