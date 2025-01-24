#include "Star.h"

Star::Star()
{
}

Star::~Star()
{
}

void Star::SetPosition(Vector3 position)
{
	this->position = position;
}

void Star::SetColor(Color color)
{
	this->color = color;
}

void Star::SetName(std::string name)
{
	this->name = name;
}

Vector3 Star::GetPosition()
{
	return position;
}

Color Star::GetColor()
{
	return color;
}

std::string Star::GetName()
{
	return name;
}

void Star::SetSize(float size)
{
	this->size = size;
}

float Star::GetSize()
{
	return this->size;
}
