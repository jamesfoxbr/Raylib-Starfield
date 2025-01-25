#ifndef H_CONTROLS_H
#define H_CONTROLS_H

#include <raylib.h>

class Controls
{
public:
	Vector3 cameraPosition = {0.0f, 0.0f, 0.0f};
	Vector3 cameraRotation = {0.0f, 0.0f, 0.0f};

	Controls();
	~Controls();

	void Move();

private:
	float speed = 0.2f;
};

#endif // !H_CONTROLS_H
