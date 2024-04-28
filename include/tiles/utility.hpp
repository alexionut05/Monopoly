#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "tile.hpp"
#include <array>

class Utility : public Tile {
public:
	// Constructor and Destructor
	Utility();
	~Utility();

	// Getters
	int GetTileCost() const;
	std::array<int, 2> GetDiceMultiplier() const;

private:
	const int tile_cost_ = 150;
	const std::array<int, 2> dice_multiplier_ = {4, 10};
};

#endif // "UTILITY_HPP"