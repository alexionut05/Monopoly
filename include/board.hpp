#ifndef BOARD_HPP
#define BOARD_HPP

#include "custom_except.hpp"
#include "tiles/card_tile.hpp"
#include "tiles/free_parking.hpp"
#include "tiles/go_to_jail.hpp"
#include "tiles/go.hpp"
#include "tiles/jail.hpp"
#include "tiles/property.hpp"
#include "tiles/railroad.hpp"
#include "tiles/tax.hpp"
#include "tiles/utility.hpp"
#include "tile.hpp"
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

	// Tile methods
	void InitTile(const size_t i);
	void InitCardTile(const size_t i);
	void InitFreeParking(const size_t i);
	void InitGoToJail(const size_t i);
	void InitGo(const size_t i);
	void InitJail(const size_t i);
	void InitProperty(const size_t i);
	void InitRailroad(const size_t i);
	void InitTax(const size_t i);
	void InitUtility(const size_t i);

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