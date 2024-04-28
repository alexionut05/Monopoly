#ifndef BOARD_HPP
#define BOARD_HPP

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
#include <memory>

#include <nlohmann/json.hpp>

class Board {
public:
	// Constructor and Destructor
	Board(const int bail_value, const std::string &bank_name);
	~Board();

	// Board methods
	void InitBoard(const std::string &language);

	// Tile methods
	void InitCardTile(const nlohmann::json &j, const size_t i);
	void InitFreeParking(const nlohmann::json &j, const size_t i);
	void InitGoToJail(const nlohmann::json &j, const size_t i);
	void InitGo(const nlohmann::json &j, const size_t i);
	void InitJail(const nlohmann::json &j, const size_t i);
	void InitProperty(const nlohmann::json &j, const size_t i);
	void InitRailroad(const nlohmann::json &j, const size_t i);
	void InitTax(const nlohmann::json &j, const size_t i);
	void InitUtility(const nlohmann::json &j, const size_t i);

	// Getters
	std::unique_ptr<Tile>& GetTileAt(const size_t i);
	int GetBoardSize() const;
	int GetBailValue() const;
	std::string GetBankName() const;	

	// Operator Overloads
	friend std::ostream& operator<<(std::ostream &os, const Board &board);

private:
	std::array<std::unique_ptr<Tile>, 40> tiles_;
	const int bail_value_;
	const std::string bank_name_;
};

#endif // "BOARD_HPP"