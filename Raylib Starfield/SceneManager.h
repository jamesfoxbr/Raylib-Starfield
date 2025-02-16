// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: SceneManager.h
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

#ifndef H_SCENE_MANAGER_H
#define H_SCENE_MANAGER_H

#include "Scene.h"


class SceneManager {
public:
    Scene* currentScene = nullptr;

	// Change the current scene to a new scene and delete the old scene
    void ChangeScene(Scene* newScene) 
    {
        if (currentScene) {
            currentScene->Unload();
            delete currentScene;
        }
        currentScene = newScene;
        currentScene->Init();
    }
};

#endif // !H_SCENE_MANAGER_H



