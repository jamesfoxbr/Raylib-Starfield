#ifndef H_STAR_H
#define H_STAR_H

#include <string>
#include "raylib.h"

class Star
{
public:

	Star();
	~Star();

	void SetPosition(Vector3 position);
	void SetColor(Color color);
	void SetName(std::string name);

	Vector3 GetPosition();
	Color GetColor();
	std::string GetName();
	void SetSize(float size);
	float GetSize();

private:
	Vector3 position;
	Color color;
	std::string name;
	float size;
};

#endif // !H_STAR_H
