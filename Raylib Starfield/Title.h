#ifndef H_TITLE_H

#include <raylib.h>

#include "Scene.h"

class Title : public Scene
{
public:
	Title();
	~Title();

    void Init();
    void Update();
    void Draw2D();
    void Draw3D();
    void Unload();

private:

};

#endif // !H_TITLE_H
