#ifndef CARD_TILE_HPP
#define CARD_TILE_HPP

#include "tile.hpp"

class CardTile : public Tile {
public:
	// Constructor and Destructor
	CardTile(std::string &name, std::string &owner);
	~CardTile();

	// Print
	void Print(std::ostream &os) const;
};

#endif // "CARD_TILE_HPP"