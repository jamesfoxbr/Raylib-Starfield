#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include "Starfield.h"
#include "Utils.h"

class Space
{
public:
	Space(Camera& camera);
	~Space();
	void Update();
	
private:
	Camera& camera;
	std::vector<Starfield> starfields;

	void InstantiateStarfield();
};
#endif 
