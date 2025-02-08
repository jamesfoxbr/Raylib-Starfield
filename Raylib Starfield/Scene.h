#ifndef H_SCENE_H
#define H_SCENE_H

// Base class for a scene
class Scene {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw2D() = 0;
    virtual void Draw3D() = 0;
    virtual void Unload() = 0;
    virtual ~Scene() {} // Virtual destructor
};

#endif // !H_SCENE_H
