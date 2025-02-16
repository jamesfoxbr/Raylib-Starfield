// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: ResourceManager.h
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

#ifndef H_RESOURCE_MANAGER_H
#define H_RESOURCE_MANAGER_H

#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
public:
    static Texture2D& GetTexture(const std::string& filename);
    static Font& GetFont(const std::string& filename);
    static Sound& GetSound(const std::string& filename);
    static Model& GetModel(const std::string& filename);
    static Shader& GetShader(const std::string& vsFilename, const std::string& fsFilename);
    static void UnloadResources();
    
private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, Font> fonts;
    static std::unordered_map<std::string, Sound> sounds;
    static std::unordered_map<std::string, Model> models;
    static std::unordered_map<std::string, Shader> shaders;
};

#endif // !H_RESOURCE_MANAGER_H


