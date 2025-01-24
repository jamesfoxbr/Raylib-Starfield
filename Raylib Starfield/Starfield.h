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
	Starfield(int starCount, int starDrawDistance);
	~Starfield();
	void InitializeStars(int starCount, int starDrawDistance, int width, int height, int depth);
	void DrawStars(Camera& camera);

private:
	std::vector<Star> stars;
	int starDrawDistance;
	int width;
	int height;
	int depth;
};

#endif // !H_STARFIELD



