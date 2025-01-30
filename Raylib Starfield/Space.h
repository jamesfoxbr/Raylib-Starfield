#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include <unordered_set>
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
	
private:
	Camera& camera;
	std::vector<Starfield> starfields;
	std::mt19937 random;
	std::vector<Star*> starsPtr = {0};

	int starDrawDistance = 100; // how far the stars will be drawn from the camera
	Vector3 cameraForward = Vector3Subtract(camera.target, camera.position);
	Vector3 toStar;
	float dotProduct;

	void InstantiateStarfield();
	void UpdateLocalStarArray();
	void DrawStars(const Star* star);

	const void StarClicked(const Star* star);

	Mesh sphereMesh = GenMeshSphere(0.1f, 4, 5); // Generate a sphere mesh
	Material material = LoadMaterialDefault(); // Load default material
};
#endif 
