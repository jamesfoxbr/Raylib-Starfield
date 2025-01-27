#ifndef H_SPACE_H
#define H_SPACE_H

#include <raylib.h>
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

	void UpdateChunk();
	void ProcessChunk();
	void InstantiateStarfield(Vector3 chunkCoords);
	void UnloadFarChunks(Vector3 chunkCoords);
};
#endif 
