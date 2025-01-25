#ifndef H_STAR_H
#define H_STAR_H

#include <string>
#include "raylib.h"
#include "Utils.h"

class Star
{
public:

	Star();
	~Star();

	void SetPosition(Vector3 position);
	void SetColor();
	void SetName(std::string name);
	Vector3 GetPosition();
	Color GetColor();
	std::string GetName();
	void SetSize(float size);
	float GetSize();
	char SpectralClass();

private:
	Vector3 position;
	Color color;
	std::string name;
	float size;
	char spectralClass;
};

#endif // !H_STAR_H
