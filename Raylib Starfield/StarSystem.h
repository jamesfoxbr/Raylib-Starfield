#ifndef H_STAR_SYSTEM_H
#define H_STAR_SYSTEM_H

#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "Controls.h"
#include "Gui.h"

class StarSystem : public Scene
{
public:
	StarSystem();
	~StarSystem();
	void Init() override;   // Called when the scene is loaded
	void Update() override;	// Called every frame
	void Draw2D() override;	// Called every frame to draw 2D elements
	void Draw3D() override;	// Called every frame to draw 3D elements
	void Unload() override;	// Called when the scene is unloaded

private:
	Vector3 position;
};

#endif // !H_STAR_SYSTEM_H



