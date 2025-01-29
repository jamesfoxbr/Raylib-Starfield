#include "Star.h"



Star::Star()
{
	spectralClass = SpectralClass();
	SetColor();
}

Star::~Star()
{
}

void Star::SetPosition(const Vector3 position)
{
	this->position = position;
}

void Star::SetColor()
{
	// TODO: Make more customized colors to look more realistic
	if (spectralClass == 'O')
	{
		color = DARKBLUE;
	}
	if (spectralClass == 'B')
	{
		color = BLUE;
	}
	if (spectralClass == 'A')
	{
		color = SKYBLUE;
	}
	if (spectralClass == 'F')
	{
		color = WHITE;
	}
	if (spectralClass == 'G')
	{
		color = YELLOW;
	}
	if (spectralClass == 'K')
	{
		color = ORANGE;
	}
	if (spectralClass == 'M')
	{
		color = RED;
	}
}

void Star::SetName(const std::string name)
{
	this->name = name;
}

const Vector3 Star::GetPosition() const
{
	return position;
}

const Color Star::GetColor() const
{
	return color;
}

std::string Star::GetName()
{
	return name;
}

void Star::SetSize(const float size)
{
	this->size = size;
}

const float Star::GetSize()
{
	return this->size;
}

const char Star::SpectralClass()
{
	// TODO: correct star percentages. This is just a placeholder
	int roll = diceRoller(0, 100);

	if (roll < 1)
	{
		return 'O';
	}
	else if (roll < 2)
	{
		return 'B';
	}
	else if (roll < 3)
	{
		return 'A';
	}
	else if (roll < 4)
	{
		return 'F';
	}
	else if (roll < 8)
	{
		return 'G';
	}
	else if (roll < 76)
	{
		return 'K';
	}
	else
	{
		return 'M';
	}
}
