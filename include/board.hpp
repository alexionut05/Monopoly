#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <fstream>
#include "tile.hpp"
#include "json.hpp"

class Board {
public:
	// Constructor and Destructor
	Board();
	~Board();

	// Board methods
	void InitBoard(const std::string &language);

private:
	std::array<Tile, 40> tiles_;
};

#endif // "BOARD_HPP"