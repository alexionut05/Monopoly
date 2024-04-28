#ifndef RAIlROAD_HPP
#define RAILROAD_HPP

#include "tile.hpp"

class Railroad : public Tile {
public:
	// Constructor and Destructor
	Railroad(const int tile_cost, const std::string &name, const std::string &owner, const std::array<int, 4> rent);
	~Railroad();

	// Getters
	int GetTileLevel() const;
	std::array<int, 4> GetRent() const;

	// Print
	void Print(std::ostream &os) const;

private:
	int tile_level_;
	const std::array<int, 4> rent_;
};

#endif // "RAIlROAD_HPP"