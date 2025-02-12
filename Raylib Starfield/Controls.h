// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Controls.h
// Description: Controls for the Raylib Starfield project
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

#ifndef H_CONTROLS_H
#define H_CONTROLS_H

#include <raylib.h>
#include <iostream>
#include <imgui.h>

class Controls
{
public:
	Controls();
	~Controls();

	void Update();
	void Move();
	void MouseLook();
	Vector3 GetCameraPostion();
	Vector3 GetCameraRotation();

private:
	Vector2 CurrentMousePosition; 
	Vector2 LastMousePosition;
	float   mouseSensibility = 0.1f; 
	Vector3 velocity = {0.0f, 0.0f, 0.0f};       // Current camera velocity
	Vector3 cameraPosition = {1.0f, 0.0f, 0.0f}; // Current camera position
	Vector3 cameraRotation = {0.0f, 0.0f, 0.0f}; // Current camera rotation
	bool    cursorEnable = true;

	float speed = 0.2f;
	float maxVelocity = 2.0f;
	float deceleration = 0.3f;
};

#endif // !H_CONTROLS_H
