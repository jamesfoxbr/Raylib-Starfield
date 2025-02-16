
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


