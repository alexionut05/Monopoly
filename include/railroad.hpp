#ifndef RAIlROAD_HPP
#define RAILROAD_HPP

#include "tile.hpp"
#include <array>

class Railroad : public Tile {
public:
	// Constructor and Destructor
	Railroad();
	~Railroad();

	// Getters
	int GetTileCost() const;
	std::array<int, 4> GetRent() const;

private:
	const int tile_cost_ = 200;
	const std::array<int, 4> rent_ = {25, 50, 100, 200};
};

#endif // "RAIlROAD_HPP"