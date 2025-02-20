#ifndef H_PLANET_SCENE_H
#define H_PLANET_SCENE_H

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>
#include "Scene.h"


class PlanetScene : public Scene
{
public:
	virtual void Init() override;    // Called when the scene is loaded
	virtual void Update() override;  // Called every frame
	virtual void Draw2D() override;  // Called every frame to draw 2D elements
	virtual void Draw3D() override;  // Called every frame to draw 3D elements
	virtual void Unload() override;  // Called when the scene is unloaded

private:

};

#endif // !H_PLANET_SCENE_H



