// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Title.h
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

#ifndef H_TITLE_H
#define H_TITLE_H

#include <raylib.h>
#include <vector>
#include <cmath>
#include "Scene.h"
#include "Space.h" 
#include "SceneManager.h"

struct StarPixels {
    float x, y, z;
};

class Title : public Scene
{
public:
    Title();
    ~Title();

    void Init() override;    // Called when the scene is loaded
    void Update() override;  // Called every frame
    void Draw2D() override;  // Called every frame to draw 2D elements
    void Draw3D() override;  // Called every frame to draw 3D elements
    void Unload() override;  // Called when the scene is unloaded

    void Menu();

private:
    //Scene* previousScene;
    std::vector<StarPixels> stars;
    //int selectedOption = 0;
    //const int menuOptionsCount = sizeof(menuOptions) / sizeof(menuOptions[0]);
    //static constexpr const char* menuOptions[] = {"Start", "Options", "Exit"};
};

#endif // !H_TITLE_H
