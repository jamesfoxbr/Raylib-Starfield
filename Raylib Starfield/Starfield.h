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
	Starfield(int starCount, int starDrawDistance, int size);
	Starfield(int starCount, int starDrawDistance, Vector3 position);
	~Starfield();
	void InitializeStars(int starCount, int starDrawDistance, int size);
	void DrawStars(Camera& camera);
	Vector3 GetPosition();

private:
	Vector3 position = {0.0f, 0.0f, 0.0f};
	std::vector<Star> stars;
	int starDrawDistance = 100;
	int size = 100;
};

#endif // !H_STARFIELD



