#pragma once
#include <string>
#include <vector>
#include <random>

class RandomNameGenerator {
public:
    RandomNameGenerator(unsigned int seed) {}

    std::string generateName(size_t length, std::mt19937& rng) {
        std::string name;
        std::uniform_int_distribution<> dist(0, alphabet.size() - 1);
        for (size_t i = 0; i < length; ++i) {
            name += alphabet[dist(rng)];
        }
        return name;
    }

private:
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
};
