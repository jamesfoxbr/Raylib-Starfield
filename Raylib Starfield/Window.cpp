// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Window.h
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

#include "Window.h"

Window::Window()
{
	// Initialization
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "FPS-like 3D Star Field");
	
	SetTargetFPS(60);

	// Camera setup
	camera.position = Vector3{0.0f, 0.0f, 10.0f};    // Camera position (eye level about 1.75m)
	camera.target = Vector3{0.0f, 0.0f, 0.0f};       // Camera target (look at the origin)
	camera.up = Vector3{0.0f, 1.0f, 0.0f};           // Camera up direction (Y-axis)
	camera.fovy = 45.0f;                             // Field of view (in degrees)
	camera.projection = CAMERA_PERSPECTIVE;          // Set perspective projection
}

Window::~Window()
{
	// De-Initialization
	CloseWindow();
}
