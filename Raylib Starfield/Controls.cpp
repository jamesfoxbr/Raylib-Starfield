// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Controls.cpp
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

#include "Controls.h"
#include "Globals.h"

Controls::Controls()
{
	cameraPosition = {0.0f, 0.0f, 0.0f};
	CurrentMousePosition = GetMousePosition();
	LastMousePosition = CurrentMousePosition;
}

Controls::~Controls()
{
}

void Controls::Update()
{
	cameraPosition = {0.0f, 0.0f, 0.0f};
	cameraRotation = {0.0f, 0.0f, 0.0f};
	Move();
	MouseLook();
	UpdateCameraPro(&camera_ref, GetCameraPostion(), GetCameraRotation(), 0.0f);
}

void Controls::Move()
{
	// don't pass mouse and keyboard presses further if an ImGui widget is active
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return;
	}

	// Set movement speed
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		maxVelocity = 8.0f;
	}
	else
	{
		maxVelocity = 2.0f;
	}

	// Check buttons pressed
	if (IsKeyDown(KEY_W))
	{
		velocity.x += speed;
	}
	if (IsKeyDown(KEY_S))
	{
		velocity.x += -speed;
	}
	if (IsKeyDown(KEY_D))
	{
		velocity.y += speed;
	}
	if (IsKeyDown(KEY_A))
	{
		velocity.y += -speed;
	}
	if (IsKeyDown(KEY_SPACE))
	{
		velocity.z += speed;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		velocity.z += -speed;
	}

	// Control maximum velocity
	if (velocity.x > maxVelocity)
	{
		velocity.x = maxVelocity;
	}
	if (velocity.y > maxVelocity)
	{
		velocity.y = maxVelocity;
	}
	if (velocity.z > maxVelocity)
	{
		velocity.z = maxVelocity;
	}
	
	// Reduce acceleration until it reaches zero
	if (velocity.x > 0 && !IsKeyDown(KEY_W))
	{
		velocity.x -= deceleration;
		if (velocity.x < 0) velocity.x = 0;
	}
	else if (velocity.x < 0 && !IsKeyDown(KEY_S))
	{
		velocity.x += deceleration;
		if (velocity.x > 0) velocity.x = 0;
	}

	if (velocity.y > 0 && !IsKeyDown(KEY_D))
	{
		velocity.y -= deceleration;
		if (velocity.y < 0) velocity.y = 0;
	}
	else if (velocity.y < 0 && !IsKeyDown(KEY_A))
	{
		velocity.y += deceleration;
		if (velocity.y > 0) velocity.y = 0;
	}

	if (velocity.z > 0 && !IsKeyDown(KEY_SPACE))
	{
		velocity.z -= deceleration;
		if (velocity.z < 0) velocity.z = 0;
	}
	else if (velocity.z < 0 && !IsKeyDown(KEY_LEFT_CONTROL))
	{
		velocity.z += deceleration;
		if (velocity.z > 0) velocity.z = 0;
	}
	
	cameraPosition = velocity;
}

void Controls::MouseLook()
{
	// don't pass mouse and keyboard presses further if an ImGui widget is active
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return;
	}

	CurrentMousePosition = GetMousePosition();
	Vector2 storeMousePosition;
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		if (cursorEnable)
		{
			storeMousePosition = GetMousePosition();
			DisableCursor();
			SetMousePosition((int)storeMousePosition.x, (int)storeMousePosition.y);
			CurrentMousePosition = GetMousePosition();
			cursorEnable = false;
		}

		if (LastMousePosition.x != CurrentMousePosition.x)
		{
			cameraRotation.x = (CurrentMousePosition.x - LastMousePosition.x) * mouseSensibility;
		}
		if (LastMousePosition.y != CurrentMousePosition.y)
		{
			cameraRotation.y = (CurrentMousePosition.y - LastMousePosition.y) * mouseSensibility;
		}
	}
	else
	{
		if (!cursorEnable)
		{
			EnableCursor();
			cursorEnable = true;
		}
	}
	LastMousePosition = CurrentMousePosition;
}

Vector3 Controls::GetCameraPostion()
{
	return cameraPosition;
}

Vector3 Controls::GetCameraRotation()
{
	return cameraRotation;
}
