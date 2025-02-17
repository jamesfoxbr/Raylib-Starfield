// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Gui.h
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

#ifndef H_GUI_H
#define H_GUI_H

#include <string>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

class Gui
{
public:
	Gui();
	~Gui();
	void DrawInterface();
	void DebugInterface();
	void TitleInterface();
	void SpaceInterface();
	void StarSystemInterface();

	void SetStarName(std::string name);
	void SetStarClass(char Sclass); 
	void SetWindowOpen();

	void SetExitConfirmationOpen();

	void ReturnToTitle();

private:
	std::string selectedStar = "";
	bool show_demo_window = true;
	bool show_another_window = false;
	bool windowOpen = false;
	bool exitConfirmation = false;
	char starClass[1] = "";
};

#endif // !H_GUI_H
