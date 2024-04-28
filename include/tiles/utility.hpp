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
	int GetTileLevel() const;
	std::array<int, 2> GetDiceMultiplier() const;

	// Setters
	void SetTileCost(const int tile_cost);
	void SetTileLevel(const int tile_level);
	void SetDiceMultiplier(const std::array<int, 2> dice_multiplier);

	// Print
	void Print(std::ostream &os) const;

private:
	int tile_level_;
	std::array<int, 2> dice_multiplier_;
};

#endif // "UTILITY_HPP"