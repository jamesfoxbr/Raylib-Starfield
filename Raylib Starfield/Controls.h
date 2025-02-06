#ifndef H_CONTROLS_H
#define H_CONTROLS_H

#include <raylib.h>
#include <iostream>
#include <imgui.h>
#include "Globals.h"

class Controls
{
public:
	Controls(Camera& Camera);
	~Controls();

	void Update();
	void Move();
	void MouseLook();
	Vector3 GetCameraPostion();
	Vector3 GetCameraRotation();

private:
	Camera& camera;
	float speed = 0.2f;
	Vector2 CurrentMousePosition;
	Vector2 LastMousePosition;
	float mouseSensibility = 0.1f;
	Vector3 Accelleration = {0.0f, 0.0f, 0.0f};
	Vector3 cameraPosition = {1.0f, 0.0f, 0.0f};
	Vector3 cameraRotation = {0.0f, 0.0f, 0.0f};
	bool cursorEnable = true;
};

#endif // !H_CONTROLS_H
