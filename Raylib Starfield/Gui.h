#ifndef H_GUI_H
#define H_GUI_H

#include <string>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

class Gui
{
public:
	Gui();
	~Gui();
	void DrawInterface();
	void SetStarName(std::string name);
	void SetStarClass(char Sclass); 
	void SetWindowOpen();

private:
	std::string selectedStar = "";
	bool show_demo_window = true;
	bool show_another_window = false;
	bool windowOpen = false;
	char starClass[1] = "";
};

#endif // !H_GUI_H
