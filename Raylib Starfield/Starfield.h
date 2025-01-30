#ifndef H_STARFIELD
#define H_STARFIELD

#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <vector>
#include <array>
#include "Star.h"
#include "Utils.h"

class Starfield
{
public:
	Starfield(const int starCount, const int starDrawDistance, const Vector3 position, const int chunkSize, std::mt19937& random);
	~Starfield();
	const void InitializeStars(const int starCount, const int starDrawDistance, const int size, std::mt19937& random);
	const Vector3 GetPosition() const;
	const int GetNumberOfStars() const;
	const std::vector<Star>& GetStars() const { return stars; }

	Star* IsStarClicked(Camera& camera) const;

	std::string GenerateName(size_t length, std::mt19937& rng);

private:
	std::vector<Star> stars;
	Vector3 position = {0.0f, 0.0f, 0.0f};
	int size;
	int numberOfStars = 0;
};

static const std::array consonants = std::to_array<std::string>({
    // Letter Singles
"b",
"c",
"d",
"f",
"g",
"h",
"j",
"k",
"l",
"m",
"n",
"p",
"qu"
"r",
"s",
"t",
"v",
"w",
"x",
"y",
"z",
"sc",
// Blends
"ch",
"gh",
"ph",
"sh",
"th",
"wh",
"ck",
"nk",
"rk",
"sk",
"wk",
"cl",
"fl",
"gl",
"kl",
"ll",
"pl",
"sl",
"br",
"cr",
"dr",
"fr",
"gr",
"kr",
"pr",
"sr",
"tr",
"ss",
"st",
"str",
// More copies to increase frequency
"b",
"c",
"d",
"f",
"g",
"h",
"j",
"k",
"l",
"m",
"n",
"p",
"r",
"s",
"t",
"v",
"w",
"b",
"c",
"d",
"f",
"g",
"h",
"j",
"k",
"l",
"m",
"n",
"p",
"r",
"s",
"t",
"v",
"w",
"br",
"dr",
"fr",
"gr",
"kr",});

static const std::array vowels = std::to_array<std::string>({
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
"a",
"e",
"i",
"o",
"u",
// Vowel Blends
"aa",
"ae",
"ai",
"ao",
"au",
"ea",
"ee",
"ei",
"eo",
"eu",
"ia",
"ie",
"ii",
"io",
"iu",
"oa",
"oe",
"oi",
"oo",
"ou",
"eau",
"'",
"y"});

#endif // !H_STARFIELD



