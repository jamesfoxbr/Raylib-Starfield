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
	else if (spectralClass == 'B')
	{
		color = BLUE;
	}
	else if (spectralClass == 'A')
	{
		color = SKYBLUE;
	}
	else if (spectralClass == 'F')
	{
		color = RED;
	}
	else if (spectralClass == 'G')
	{
		color = YELLOW;
	}
	else if (spectralClass == 'K')
	{
		color = ORANGE;
	}
	else
	{
		color = WHITE;
	}
}

void Star::SetName(const std::string& name)
{
	this->name = name;
}

const Vector3& Star::GetPosition() const 
{
	return position;
}

const Color& Star::GetColor() const
{
	return color;
}

const std::string& Star::GetName() const
{
	return name;
}

void Star::SetSize(const float size)
{
	this->size = size;
}

const float& Star::GetSize() const
{
	return this->size;
}

const char Star::SpectralClass()
{
	// TODO: correct star percentages. This is just a placeholder
	const int roll = diceRoller(0, 100);

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
