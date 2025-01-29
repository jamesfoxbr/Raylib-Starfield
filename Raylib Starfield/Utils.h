#ifndef H_UTILS_H
#define H_UTILS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "raylib.h"
#include "Globals.h"

int diceRoller(int minimun, int maximun);
double distance(Vector3 p1, Vector3 p2);
void DrawCoordinates(const Camera& camera);
void targetCursor();
void DrawDebugText(const std::string& text, int x, int y, int fontSize, Color color);

#endif // !H_UTILS_H

