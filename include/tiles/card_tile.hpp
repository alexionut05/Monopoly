#ifndef CARD_TILE_HPP
#define CARD_TILE_HPP

#include "tile.hpp"

class CardTile : public Tile {
public:
	CardTile(const std::string &name, const std::string &owner);
	
	void Print(std::ostream &os) const;
};

#endif // "CARD_TILE_HPP"