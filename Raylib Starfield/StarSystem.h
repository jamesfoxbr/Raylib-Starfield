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
	StarSystem(Camera& camera);
	~StarSystem();
	void Init() override;
	void Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void Unload() override;

private:
	Camera& camera;
	Controls* control = nullptr;
};

#endif // !H_STAR_SYSTEM_H



