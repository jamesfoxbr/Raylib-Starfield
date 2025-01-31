#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include "Starfield.h"
#include "Utils.h"

constexpr int NUMBER_OF_STARS = 200;

class Space
{
public:
	Space(Camera& camera);
	~Space();
	void Update();
	size_t GetNumberOfStarfields()  { return starfields.size(); }
	int GetNumberOfStars();
	void Draw3D();
	void Draw2D();
	
private:
	Camera& camera;
	std::vector<Starfield> starfields;
	Star* selectedStar = nullptr;
	std::mt19937 random;

	int numberOfStars = NUMBER_OF_STARS; // number of stars in each chunk
	int chunkSize = 100; // width, height and depth of the chunk
	int chunkDrawDistance = 2;   // how many chunks will draw in each direction from the central chunk de camera is at momenet
	int starDrawDistance = 100; // how far the stars will be drawn from the camera

	int camX;
	int camY;
	int camZ;

	const int fontSize = 20; // Define the font size of star names
	Image image = GenImageColor(screenWidth, screenHeight, BLANK);  // Empty image (all transparent)
	Texture2D texture = LoadTextureFromImage(image);        // Convert it into a texture

	void InstantiateStarfield();
	

	Mesh sphereMesh = GenMeshSphere(0.1f, 4, 5); // Generate a sphere mesh
	Material material = LoadMaterialDefault(); // Load default material
};

static std::vector<Matrix> transforms;
static std::vector<Color> colors;

static Vector3 Position3D;
static Vector2 screenPos;
#endif 
