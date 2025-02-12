#include "Star.h"
#include "Utils.h"

Star::Star()
{
}

Star::~Star()
{
}

void Star::SetPosition(const Vector3& position)
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

void Star::SpectralClass(int r)
{
	// TODO: correct star percentages. This is just a placeholder
	const int roll = r;
	

	if (roll < 1)
	{
		spectralClass = 'O';
	}
	else if (roll < 2)
	{
		spectralClass = 'B';
	}
	else if (roll < 3)
	{
		spectralClass = 'A';
	}
	else if (roll < 4)
	{
		spectralClass = 'F';
	}
	else if (roll < 8)
	{
		spectralClass = 'G';
	}
	else if (roll < 76)
	{
		spectralClass = 'K';
	}
	else
	{
		spectralClass = 'M';
	}
	
	SetColor();
}

const char Star::GetSpectralClass() const
{
	return spectralClass;
}

Matrix Star::GetTransform() const {
	return MatrixTranslate(GetPosition().x, GetPosition().y, GetPosition().z);
}
