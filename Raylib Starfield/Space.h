#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include <iostream>
#include <string>
#include "Starfield.h"
#include "Utils.h"
#include "Gui.h"

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

	Star* IsStarClicked(const Star& star) const;
	
private:
	Camera& camera;
	Gui gui;
	std::vector<Starfield> starfields;
	Star* selectedStar = nullptr;
	std::mt19937 random;

	int starDrawDistance = 100; // how far the stars will be drawn from the camera
	int numberOfStars = NUMBER_OF_STARS; // number of stars in each chunk
	int chunkSize = 100; // width, height and depth of the chunk
	int chunkDrawDistance = 2;   // how many chunks will draw in each direction from the central chunk de camera is at momenet

	int camX = 0;
	int camY = 0;
	int camZ = 0;

	const int fontSize = 20; // Define the font size of star names
	Image image = GenImageColor(screenWidth, screenHeight, BLANK);  // Empty image (all transparent)
	Texture2D texture = LoadTextureFromImage(image);        // Convert it into a texture

	Mesh sphereMesh = GenMeshSphere(0.1f, 8, 8); // Generate a sphere mesh
	Material material = LoadMaterialDefault(); // Load default material
	Shader shader = LoadShader(TextFormat("fireball.vs"), TextFormat("fireball.fs"));
	// Create a basic checkerboard texture
	Image checkerboard;
	Texture2D checkerTexture;

	void InstantiateStarfield();
	const void DrawStarNames(const Star& star);
};

static std::vector<Matrix> transforms;
static std::vector<Color> colors;

static Vector3 Position3D;
static Vector2 screenPos;
#endif 



