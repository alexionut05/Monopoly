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
	int GetTileLevel() const;
	std::array<int, 4> GetRent() const;

	// Setters
	void SetTileCost(const int tile_cost);
	void SetTileLevel(const int tile_level);
	void SetRent(const std::array<int, 4> rent);

	// Print
	void Print(std::ostream &os) const;

private:
	int tile_level_;
	std::array<int, 4> rent_;
};

#endif // "RAIlROAD_HPP"