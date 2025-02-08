#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include "rlgl.h"
#include <stddef.h>
#include <unordered_set>

#include <iostream>
#include <string>
#include "Starfield.h"
#include "Utils.h"
#include "Gui.h"
#include "Scene.h"
#include "Controls.h"

// Hash function for Vector3
struct Vector3Hash {
	std::size_t operator()(const Vector3& v) const noexcept {
		std::size_t hx = std::hash<float>{}(v.x);
		std::size_t hy = std::hash<float>{}(v.y);
		std::size_t hz = std::hash<float>{}(v.z);
		return hx ^ (hy << 1) ^ (hz << 2); // Combine hashes
	}
};

constexpr int NUMBER_OF_STARS = 200;

class Space : public Scene
{
public:
	Space(Camera& camera);
	~Space();

	void Draw3DBillboardRec(Camera& camera, Texture2D& texture, Rectangle source, Vector3 position, Vector2 size, Color tint);
	void Draw3DBillboard(Camera& camera, Texture2D& texture, Vector3 position, float size, Color tint);

	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2D() override;
	void Unload() override;

	size_t GetNumberOfStarfields()  { return starfields->size(); }
	int GetNumberOfStars();

	Star* IsStarClicked(const Star& star);
	
private:
	Camera& camera;
	Controls* control = nullptr;
	Gui* gui = nullptr;
	std::vector<Starfield>* starfields;
	Star* selectedStar = nullptr;
	std::mt19937 random;

	static constexpr int starDrawDistance = 150;                    // how far the stars will be drawn from the camera
	static constexpr int numberOfStars = NUMBER_OF_STARS;           // number of stars in each chunk
	static constexpr int chunkSize = 100;                           // width, height and depth of the chunk
	static constexpr int chunkDrawDistance = 2;                     // how many chunks will draw in each direction from the central chunk de camera is at momenet

	int camX = 0;
	int camY = 0;
	int camZ = 0;

	int cubeSelectTimer = 0;
	Vector3 cubePos = {0};

	Image image = GenImageColor(screenWidth, screenHeight, BLANK);  // Empty image (all transparent)
	Texture2D texture = LoadTextureFromImage(image);                // Convert it into a texture

	const starMesh planeMesh = GenMeshPlane(3.0f, 3.0f, 2, 2);      // Generate a sphere mesh
	const Material material = LoadMaterialDefault();                // Load default material

	Shader shader = LoadShader("resources/shaders/fireballs.vs", "resources/shaders/fireballs.fs");

	// Create a basic checkerboard texture
	Image checkerboard;
	Texture2D checkerTexture;

	// skybox
	Model skybox;
	Texture2D skyTexture;

	// Functions
	void InstantiateStarfield();
	const void DrawStarNames(const Star& star);
};

static std::vector<Vector3> BillPositions;
static std::vector<Color> BillColors;

static Vector3 Position3D;
static Vector2 screenPos;
#endif 



