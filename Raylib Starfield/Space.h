#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include "Starfield.h"
#include "Utils.h"

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

	std::vector<Matrix> transforms;
    std::vector<Color> colors; 

	const int fontSize = 20; // Define the font size of star names
	Image image = GenImageColor(screenWidth, screenHeight, BLANK);  // Empty image (all transparent)
	Texture2D texture = LoadTextureFromImage(image);        // Convert it into a texture

	void InstantiateStarfield();
	

	Mesh sphereMesh = GenMeshSphere(0.1f, 4, 5); // Generate a sphere mesh
	Material material = LoadMaterialDefault(); // Load default material
};
#endif 
