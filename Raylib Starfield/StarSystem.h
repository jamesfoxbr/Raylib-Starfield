// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: StarSystem.h
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

#ifndef H_STAR_SYSTEM_H
#define H_STAR_SYSTEM_H

#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <vector>
#include "scene.h"
#include "Controls.h"
#include "Gui.h"
#include "Planet.h"

class StarSystem : public Scene
{
public:
	StarSystem(std::string name, Vector3 position);
	~StarSystem();

	// Virtual function overrides
	void Init() override;   // Called when the scene is loaded
	void Update() override;	// Called every frame
	void Draw2D() override;	// Called every frame to draw 2D elements
	void Draw3D() override;	// Called every frame to draw 3D elements
	void Unload() override;	// Called when the scene is unloaded

	// Getters
	std::string GetSystemName() override;
	std::string GetWorldType() override;
	float GetAtmosphericPressure() override;

private:
	// Star system details
	const Vector3 position;
	std::mt19937 mt;
	std::string starName = "";
	std::vector<float> orbitalDistances = {0.2f, 0.4f, 0.7f, 1.0f, 1.6f, 2.8f, 2.8f, 5.2f, 10.0f, 20.0f, 40.0f, 77.0f, 
		                                   154.0f, 308.0f, 615.0f, 1230.0f, 2500.0f, 4900.0f, 9800.0f, 19500.0f, 39500.0f, 78700.0f};

	// Main world
	std::string worldType = "";
	float atmosphericPressure;

	// Stars functions 
	
	// World generation functions
	void GenerateWorldType(std::mt19937& rnd);
	void GenerateAtmosphericPressure(std::mt19937& rnd);
	void GenerateOrbits(std::mt19937& rnd);
	void GeneratePlanets(std::mt19937& rnd);
};

#endif // !H_STAR_SYSTEM_H



