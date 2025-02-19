// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: StarSystem.cpp
// Description: StarSystem class implementation.
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

#include "StarSystem.h"
#include "Globals.h"
#include "Utils.h"

StarSystem::StarSystem(std::string name,  Vector3 position)
	:
	position(position),
	starName(name),
	atmosphericPressure(0)
{
	loadedScene = STARSYSTEM;
    mt.seed(static_cast<unsigned int>(position.x) + static_cast<unsigned int>(position.y) + static_cast<unsigned int>(position.z));

	camera_ref.position = this->position;

	camera_ref.position.y += 15.0f;	
	camera_ref.position.z += 15.0f;

	// Main world basic generation
	GenerateWorldType(mt);
	GenerateAtmosphericPressure(mt);
}

StarSystem::~StarSystem()
{
}

void StarSystem::Init()
{
}

void StarSystem::Update()
{

}

void StarSystem::Draw2D()
{
}

void StarSystem::Draw3D()
{
	// Draw the primary star
	DrawSphere(position, 1, WHITE);

	// Orbit lines
	for (int i = 0; i < 10; i++)
	{
		DrawCircle3D(position, static_cast<float>(i * 5), Vector3{1, 0, 0}, 90, WHITE);
	}
}

void StarSystem::Unload()
{
}

std::string StarSystem::GetSystemName()
{
	return this->starName;
}

std::string StarSystem::GetWorldType()
{
	return this->worldType;
}

float StarSystem::GetAtmosphericPressure()
{
	return this->atmosphericPressure;
}

void StarSystem::GenerateWorldType(std::mt19937& rnd)
{
	int roll = diceRoller(1, 6, 3, rnd);
	int secondRoll = diceRoller(1, 6, 3, rnd);

	if (roll <= 7)
	{ 
		switch (secondRoll)
		{
		case 3:
			worldType = "Standard (Chthonian)";
			break;
		case 4:
			worldType = "Standard (Chthonian)";
			break;
		case 5:
			worldType = "Standard (Greenhouse)";
			break;
		case 6:
			worldType = "Standard (Greenhouse)";
			break;
		case 7:
			worldType = "Tiny (Sulfur)";
			break;
		case 8:
			worldType = "Tiny (Sulfur)";
			break;
		case 9:
			worldType = "Tiny (Sulfur)";
			break;
		case 10:
			worldType = "Standard (Ammonia)";
			break;
		case 11:
			worldType = "Standard (Ammonia)";
			break;
		case 12:
			worldType = "Standard (Ammonia)";
			break;
		case 13:
			worldType = "Large (Ammonia)";
			break;
		case 14:
			worldType = "Large (Ammonia)";
			break;
		case 15:
			worldType = "Large (Greenhouse)";
			break;
		case 16:
			worldType = "Large (Greenhouse)";
			break;
		case 17:
			worldType = "Large (Chthonian)";
			break;
		case 18:
			worldType = "Large (Chthonian)";
			break;

		default:
			break;
		}
	}
	else if (roll >= 8 && roll <= 13)
	{
		switch (secondRoll)
		{
		case 3:
			worldType = "Small (Hadean)";
			break;
		case 4:
			worldType = "Small (Ice)";
			break;
		case 5:
			worldType = "Small (Rock)";
			break;
		case 6:
			worldType = "Small (Rock)";
			break;
		case 7:
			worldType = "Tiny (Rock)";
			break;
		case 8:
			worldType = "Tiny (Rock)";
			break;
		case 9:
			worldType = "Tiny (Ice)";
			break;
		case 10:
			worldType = "Tiny (Ice)";
			break;
		case 11:
			worldType = "Asteroid Belt";
			break;
		case 12:
			worldType = "Asteroid Belt";
			break;
		case 13:
			worldType = "Standard (Ocean)";
			break;
		case 14:
			worldType = "Standard (Ocean)";
			break;
		case 15:
			worldType = "Standard(Ice)";
			break;
		case 16:
			worldType = "Standard (Hadean)";
			break;
		case 17:
			worldType = "Large (Ocean)";
			break;
		case 18:
			worldType = "Large (Ice)";
			break;

		default:
			break;
		}
	}
	else
	{
		switch (secondRoll)
		{
		case 3:
			worldType = "Standard (Garden)";
			break;
		case 4:
			worldType = "Standard (Garden)";
			break;
		case 5:
			worldType = "Standard (Garden)";
			break;
		case 6:
			worldType = "Standard (Garden)";
			break;
		case 7:
			worldType = "Standard (Garden)";
			break;
		case 8:
			worldType = "Standard (Garden)";
			break;
		case 9:
			worldType = "Standard (Garden)";
			break;
		case 10:
			worldType = "Standard (Garden)";
			break;
		case 11:
			worldType = "Standard (Garden)";
			break;
		case 12:
			worldType = "Standard (Garden)";
			break;
		case 13:
			worldType = "Standard (Garden)";
			break;
		case 14:
			worldType = "Standard (Garden)";
			break;
		case 15:
			worldType = "Standard (Garden)";
			break;
		case 16:
			worldType = "Standard (Garden)";
			break;
		case 17:
			worldType = "Large (Garden)";
			break;
		case 18:
			worldType = "Large (Garden)";
			break;

		default:
			break;
		}
	}
}

void StarSystem::GenerateAtmosphericPressure(std::mt19937& rnd)
{
	if (worldType == "Asteroid Belt" ||
		worldType == "Small (Ice)" ||
		worldType == "Tiny (Rock)" ||
		worldType == "Tiny (Sulfur)" ||
		worldType == "Small (Hadean)" ||
		worldType == "Small (Rock)")
	{
		atmosphericPressure = 0.0f;
	}
	else
	{
		atmosphericPressure = static_cast<float>(diceRoller(1, 6, 3, rnd)) / 10.0f;
	}
}


