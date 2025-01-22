#ifndef H_STAR_H
#define H_STAR_H

#include <string>
#include "raylib.h"

class Star
{
public:
	Vector3 position;
	Color color;
	std::string name;

	Star();
	~Star();

private:

};

#endif // !H_STAR_H
