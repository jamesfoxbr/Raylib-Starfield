// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Space.h
// Description: Main entry point for the Raylib Starfield project.
//
// License: Proprietary
// 
// This software is the confidential and proprietary information of Marcio Marchado Ribeiro
// ("Confidential Information"). You shall not disclose such Confidential Information and shall use
// it only in accordance with the terms of the license agreement you entered into with Marcio Marchado Ribeiro.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Author: Marcio Marchado Ribeiro
// Version: 0.1
// --------------------------------------------------------------------------------------------

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
#include "Scene.h"
#include "Controls.h"
#include "SceneManager.h"
#include "StarSystem.h"
#include "Globals.h"

// Hash function for Vector3 type (used by std::unordered_map) 
struct Vector3Hash {
	std::size_t operator()(const Vector3& v) const noexcept {
		std::size_t hx = std::hash<float>{}(v.x);
		std::size_t hy = std::hash<float>{}(v.y);
		std::size_t hz = std::hash<float>{}(v.z);
		return hx ^ (hy << 1) ^ (hz << 2); // Combine hashes
	}
};

constexpr int NUMBER_OF_STARS = 200;

// This class represents the space scene, where the stars are drawn
class Space : public Scene
{
public:
	Space();
	~Space();

	void Draw3DBillboardRec(Texture2D& texture, Rectangle source, Vector3 position, Vector2 size, Color tint);
	void Draw3DBillboard( Texture2D& texture, Vector3 position, float size, Color tint);

	void Init() override;   // Called when the scene is loaded
	void Update() override;	// Called every frame
	void Draw3D() override;	// Called every frame to draw 2D elements
	void Draw2D() override;	// Called every frame to draw 3D elements
	void Unload() override;	// Called when the scene is unloaded

	size_t GetNumberOfStarfields()  { return starfields->size(); }
	int GetNumberOfStars();

	Star* IsStarClicked(const Star& star);
	
private:
	std::vector<Starfield>* starfields;
	std::mt19937 random;

	static constexpr int starDrawDistance = 150;          // how far the stars will be drawn from the camera
	static constexpr int numberOfStars = NUMBER_OF_STARS; // number of stars in each chunk
	static constexpr int chunkSize = 100;                 // width, height and depth of the chunk
	static constexpr int chunkDrawDistance = 2;           // how many chunks will draw in each direction from the central chunk de camera is at momenet

	int camX = 0; 
	int camY = 0;
	int camZ = 0;

	int cubeSelectTimer = 0; 
	Vector3 cubePos    = {0};

	Image image = GenImageColor(screenWidth, screenHeight, BLANK);  // Empty image (all transparent) 
	Texture2D texture = LoadTextureFromImage(image);                // Convert it into a texture

	const starMesh planeMesh = GenMeshPlane(3.0f, 3.0f, 2, 2);      // Generate a sphere mesh
	const Material material = LoadMaterialDefault();                // Load default material

	Model& cubeModel             = resourceManager_ref.GetModel("resources/models/cube.obj");
	Texture& checkerBoardTexture = resourceManager_ref.GetTexture("resources/images/checkerboard.png");

	// Shader responsible for the fireballs effect (stars glowing)
	Shader& shader = resourceManager_ref.GetShader("resources/shaders/fireballs.vs", "resources/shaders/fireballs.fs");

	void InstantiateStarfield();                 // this function creates the starfield in chunks
	const void DrawStarNames(const Star& star);  // this function draws the names of the stars above them
};

static std::vector<Vector3> BillPositions;       // positions of the billboards facing the camera
static std::vector<Color>   BillColors;	         // colors of the billboards facing the camera

static Vector3 Position3D;
static Vector2 screenPos;
#endif 



