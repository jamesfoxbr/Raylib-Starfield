// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: Scene.h
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

#ifndef H_SCENE_H
#define H_SCENE_H

// Base class for a scene
class Scene {
public:
	virtual void Init()   = 0;  // Called when the scene is loaded
	virtual void Update() = 0;  // Called every frame
	virtual void Draw2D() = 0;  // Called every frame to draw 2D elements
	virtual void Draw3D() = 0;  // Called every frame to draw 3D elements
	virtual void Unload() = 0;  // Called when the scene is unloaded
    virtual ~Scene() {}         // Virtual destructor

	virtual int GetNumberOfStars() { return 0; }
};

#endif // !H_SCENE_H
