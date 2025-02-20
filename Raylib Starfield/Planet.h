#ifndef H_PLANET_H
#define H_PLANET_H

#include <raylib.h>
#include <string>

class Planet
{
public:
	Vector3 position = {0};
	std::string name = "";
	float orbitalDistanceAU = 0.0f;
};

#endif // !H_PLANET_H



