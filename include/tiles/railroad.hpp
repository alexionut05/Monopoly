#ifndef RAIlROAD_HPP
#define RAILROAD_HPP

#include "tile.hpp"

class Railroad : public Tile {
public:
	Railroad(const int tile_cost, const std::string &name, const std::string &owner, const std::array<int, 4> rent);

	int GetTileLevel() const;
	std::array<int, 4> GetRent() const;

	void SetTileLevel(const int tile_level);
	
	void Print(std::ostream &os) const;

private:
	int tile_level_;
	const std::array<int, 4> rent_;
};

#endif // "RAIlROAD_HPP"