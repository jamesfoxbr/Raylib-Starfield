#ifndef H_GUI_H
#define H_GUI_H

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
	

private:
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
};

#endif // !H_GUI_H
