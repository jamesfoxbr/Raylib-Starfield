#ifndef H_CONTROLS_H
#define H_CONTROLS_H

#include <raylib.h>

class Controls
{
public:
	Vector3 cameraPosition = {1.0f, 0.0f, 0.0f};
	Vector3 cameraRotation = {0.0f, 0.0f, 0.0f};

	Controls();
	~Controls();

	void Move();
	void MouseLook();

private:
	float speed = 0.2f;
	Vector2 CurrentMousePosition;
	Vector2 LastMousePosition;
};

#endif // !H_CONTROLS_H
