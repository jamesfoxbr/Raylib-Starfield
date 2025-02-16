// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Star.h
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

#ifndef H_STAR_H
#define H_STAR_H

#include "raylib.h"
#include "raymath.h"
#include <string>

class Star
{
public:

	Star();
	~Star();

	void SetPosition(const Vector3& position);
	void SetColor();
	void SetName(const std::string& name);
	const Vector3& GetPosition() const;
	const Color& GetColor() const;
	const std::string& GetName() const;
	void SetSize(const float size);
	const float& GetSize() const;
	void SpectralClass(int r);
	const char GetSpectralClass() const;
    Matrix GetTransform() const;

private:
	Vector3 position;
	Color color;
	std::string name;
	float size;
	char spectralClass;
};

#endif // !H_STAR_H
