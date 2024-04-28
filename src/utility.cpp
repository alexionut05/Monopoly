#include "utility.hpp"

// Constructor and Destructor
Utility::Utility() {}

Utility::~Utility() {}

// Getters
int Utility::GetTileCost() const
{
	return tile_cost_;
}

std::array<int, 2> Utility::GetDiceMultiplier() const
{
	return dice_multiplier_;
}