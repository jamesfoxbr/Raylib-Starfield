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

StarSystem::StarSystem()
{
	this->position = camera_ref.position;
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


