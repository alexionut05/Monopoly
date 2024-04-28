#ifndef FREE_PARKING_HPP
#define FREE_PARKING_HPP

#include "tile.hpp"
#include <iostream>

class FreeParking : public Tile {
public:
	// Constructor and Destructor
	FreeParking();
	~FreeParking();

	// Print
	void Print(std::ostream &os) const;
};

#endif // "FREE_PARKING_HPP"