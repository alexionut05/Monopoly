#ifndef CARD_TILE_HPP
#define CARD_TILE_HPP

#include "tile.hpp"
#include <iostream>

class CardTile : public Tile {
public:
	// Constructor and Destructor
	CardTile();
	~CardTile();

	// Print
	void Print(std::ostream &os) const;
};

#endif // "CARD_TILE_HPP"