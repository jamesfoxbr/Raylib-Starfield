#ifndef H_STAR_H
#define H_STAR_H

#include "raylib.h"
#include "Utils.h"

class Star
{
public:

	Star();
	~Star();

	void SetPosition(const Vector3 position);
	void SetColor();
	void SetName(const std::string& name);
	const Vector3& GetPosition() const;
	const Color& GetColor() const;
	const std::string& GetName() const;
	void SetSize(const float size);
	const float& GetSize() const;
	void SpectralClass(int r);
	char GetSpectralClass();

private:
	Vector3 position;
	Color color;
	std::string name;
	float size;
	char spectralClass;
};

#endif // !H_STAR_H
