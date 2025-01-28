#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
#include <unordered_map>
#include "Starfield.h"

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
	void UnloadFarChunks();
};
#endif 
