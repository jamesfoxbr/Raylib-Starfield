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
};

#endif // !H_SCENE_H
