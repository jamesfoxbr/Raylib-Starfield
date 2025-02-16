// --------------------------------------------------------------------------------------------
// Project: Raylib Starfield
// File: ResourceManager.cpp
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

#include "ResourceManager.h"

// Static member initialization
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Font> ResourceManager::fonts;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Model> ResourceManager::models;
std::unordered_map<std::string, Shader> ResourceManager::shaders;

Texture2D& ResourceManager::GetTexture(const std::string& filename)
{
    if (textures.find(filename) == textures.end()) {
        textures[filename] = LoadTexture(filename.c_str());
    }
    return textures[filename];
}

Font& ResourceManager::GetFont(const std::string& filename)
{
    if (fonts.find(filename) == fonts.end()) {
        fonts[filename] = LoadFont(filename.c_str());
    }
    return fonts[filename];
}

Sound& ResourceManager::GetSound(const std::string& filename)
{
    if (sounds.find(filename) == sounds.end()) {
        sounds[filename] = LoadSound(filename.c_str());
    }
    return sounds[filename];
}

Model& ResourceManager::GetModel(const std::string& filename)
{
    if (models.find(filename) == models.end()) {
        models[filename] = LoadModel(filename.c_str());
    }
    return models[filename];
}

Shader& ResourceManager::GetShader(const std::string& vsFilename, const std::string& fsFilename)
{
    std::string key = vsFilename + ":" + fsFilename;
    if (shaders.find(key) == shaders.end()) 
    {
        shaders[key] = LoadShader(vsFilename.c_str(), fsFilename.c_str());
    }
    return shaders[key];
}

void ResourceManager::UnloadResources() 
{
    for (auto& [key, texture] : textures) {
        UnloadTexture(texture);
    }
    for (auto& [key, font] : fonts) {
        UnloadFont(font);
    }
    for (auto& [key, sound] : sounds) {
        UnloadSound(sound);
    }
    for (auto& [key, model] : models) {
        UnloadModel(model);
    }
    for (auto& [key, shader] : shaders) {
        UnloadShader(shader);
    }

    textures.clear();
    fonts.clear();
    sounds.clear();
    models.clear();
    shaders.clear();
}

