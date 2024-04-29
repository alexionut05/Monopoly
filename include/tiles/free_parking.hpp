#ifndef FREE_PARKING_HPP
#define FREE_PARKING_HPP

#include "tile.hpp"

class FreeParking : public Tile {
public:
	FreeParking(const std::string &name, const std::string &owner);
	
	void Print(std::ostream &os) const;
};

#endif // "FREE_PARKING_HPP"