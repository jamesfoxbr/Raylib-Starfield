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
#include "scene.h"
#include "Controls.h"
#include "Gui.h"

class StarSystem : public Scene
{
public:
	StarSystem(std::string name, Vector3 position);
	~StarSystem();
	void Init() override;   // Called when the scene is loaded
	void Update() override;	// Called every frame
	void Draw2D() override;	// Called every frame to draw 2D elements
	void Draw3D() override;	// Called every frame to draw 3D elements
	void Unload() override;	// Called when the scene is unloaded

	std::string GetSystemName() override;

	std::string GetWorldType() override;

	float GetAtmosphericPressure() override;

private:
	const Vector3 position;
	std::mt19937 mt;
	std::string starName = "";
	
	unsigned int numberOfPlanets;

	// Main world
	std::string worldType = "";
	float atmosphericPressure;

	void GenerateWorldType(std::mt19937& rnd);
	void GenerateAtmosphericPressure(std::mt19937& rnd);

};

#endif // !H_STAR_SYSTEM_H



