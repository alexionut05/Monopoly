#ifndef CARD_TILE_HPP
#define CARD_TILE_HPP

#include "tile.hpp"

class CardTile : public Tile {
public:
	CardTile(const std::string &name, const std::string &owner);
	
	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;
};

#endif // "CARD_TILE_HPP"