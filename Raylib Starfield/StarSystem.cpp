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
#include <map>
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
    int roll       = diceRoller(1, 6, 3, rnd);
    int secondRoll = diceRoller(1, 6, 3, rnd);

    std::map<int, std::string> worldTypeMap;

    if (roll <= 7)
    {
        worldTypeMap = {
            {3, "Standard (Chthonian)"}, {4, "Standard (Chthonian)"}, {5, "Standard (Greenhouse)"}, {6, "Standard (Greenhouse)"},
            {7, "Tiny (Sulfur)"},        {8, "Tiny (Sulfur)"},        {9, "Tiny (Sulfur)"},         {10, "Standard (Ammonia)"}, 
			{11, "Standard (Ammonia)"}, {12, "Standard (Ammonia)"},   {13, "Large (Ammonia)"},      {14, "Large (Ammonia)"},
            {15, "Large (Greenhouse)"}, {16, "Large (Greenhouse)"},   {17, "Large (Chthonian)"},    {18, "Large (Chthonian)"}
        };
    }
    else if (roll >= 8 && roll <= 13)
    {
        worldTypeMap = {
            {3, "Small (Hadean)"},  {4, "Small (Ice)"},        {5, "Small (Rock)"},      {6, "Small (Rock)"},
            {7, "Tiny (Rock)"},     {8, "Tiny (Rock)"},        {9, "Tiny (Ice)"},        {10, "Tiny (Ice)"},
            {11, "Asteroid Belt"},  {12, "Asteroid Belt"},     {13, "Standard (Ocean)"}, {14, "Standard (Ocean)"},
            {15, "Standard (Ice)"}, {16, "Standard (Hadean)"}, {17, "Large (Ocean)"},    {18, "Large (Ice)"}
        };
    }
    else
    {
        worldTypeMap = {
            {3, "Standard (Garden)"},  {4, "Standard (Garden)"},  {5, "Standard (Garden)"},  {6, "Standard (Garden)"},
            {7, "Standard (Garden)"},  {8, "Standard (Garden)"},  {9, "Standard (Garden)"},  {10, "Standard (Garden)"},
            {11, "Standard (Garden)"}, {12, "Standard (Garden)"}, {13, "Standard (Garden)"}, {14, "Standard (Garden)"},
            {15, "Standard (Garden)"}, {16, "Standard (Garden)"}, {17, "Large (Garden)"},    {18, "Large (Garden)"}
        };
    }

    worldType = worldTypeMap[secondRoll];
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

void StarSystem::GenerateOrbits(std::mt19937& rnd)
{
}

void StarSystem::GeneratePlanets(std::mt19937& rnd)
{

}


