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
	size_t GetNumberOfStarfields()  { return starfields.size(); }
	int GetNumberOfStars();
	
private:
	Camera& camera;
	std::vector<Starfield> starfields;
	std::mt19937 random;

	void InstantiateStarfield();
};
#endif 
