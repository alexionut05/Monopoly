#ifndef BOARD_HPP
#define BOARD_HPP

#include "custom_except.hpp"
#include "tile.hpp"
#include "tile_factory.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>

class Board {
public:
	Board(const int bail_value, const std::string &bank_name, const std::string &tiles_file);

	// Board methods
	void InitBoard();

	// Getters
	std::unique_ptr<Tile>& GetTileAt(const size_t i);
	size_t GetBoardSize() const;
	int GetBailValue() const;
	std::string GetBankName() const;	

	// Operator Overloads
	friend std::ostream& operator<<(std::ostream &os, const Board &board);

private:
	std::array<std::unique_ptr<Tile>, 40> tiles_;
	const int bail_value_;
	const std::string bank_name_;
	nlohmann::json tiles_data_;
};

#endif // "BOARD_HPP"