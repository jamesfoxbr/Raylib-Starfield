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
	Color GetClearColor();
	void DrawInterface();
	void SetStarName(std::string name);
	void SetStarClass(char Sclass); // Change parameter type to std::string

private:
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	std::string selectedStar = "";
	char starClass[1] = "";
};

#endif // !H_GUI_H
