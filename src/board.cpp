#include "board.hpp"

// Constructor and Destructor
Board::Board(const int bail_value, const std::string &bank_name)
	: bail_value_(bail_value), bank_name_(bank_name)
{
	for (size_t i = 0; i < tiles_.size(); ++i) {
		tiles_[i] = nullptr;
	}

}

Board::~Board() {}

// Board methods
void Board::InitBoard(const std::string &language)
{
	// Load tiles
	std::ifstream file("../locales/" + language + "/tiles.json");
	nlohmann::json j;
	file >> j;
	file.close();

	// Init tiles
	for (size_t i = 0; i < tiles_.size(); ++i) {
		std::string type = j["tiles"][i][0].get<std::string>();
		if (type == "Chance" || type == "Community Chest") {
			InitCardTile(j, i);
		} else if (type == "Free Parking") {
			InitFreeParking(j, i);
		} else if (type == "Go To Jail") {
			InitGoToJail(j, i);
		} else if (type == "Go") {
			InitGo(j, i);
		} else if (type == "Jail") {
			InitJail(j, i);
		} else if (type == "Property") {
			InitProperty(j, i);
		} else if (type == "Railroad") {
			InitRailroad(j, i);
		} else if (type == "Tax") {
			InitTax(j, i);
		} else if (type == "Utility") {
			InitUtility(j, i);
		}
	}
}

// Tile methods
void Board::InitCardTile(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();

	CardTile tile(name, bank_name_);

	tiles_[i] = std::make_unique<CardTile>(tile);
}

void Board::InitFreeParking(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();

	FreeParking tile(name, bank_name_);

	tiles_[i] = std::make_unique<FreeParking>(tile);
}

void Board::InitGoToJail(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();

	GoToJail tile(name, bank_name_);

	tiles_[i] = std::make_unique<GoToJail>(tile);
}

void Board::InitGo(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int pass_go = j["tiles"][i][2].get<int>();

	Go tile(name, bank_name_, pass_go);

	tiles_[i] = std::make_unique<Go>(tile);
}

void Board::InitJail(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int jail_bail = j["tiles"][i][2].get<int>();

	Jail tile(name, bank_name_, jail_bail);

	tiles_[i] = std::make_unique<Jail>(tile);
}

void Board::InitProperty(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int tile_cost = j["tiles"][i][2].get<int>();
	int building_cost = j["tiles"][i][3].get<int>();
	std::string colour = j["tiles"][i][4].get<std::string>();
	std::string colour_type = j["tiles"][i][5].get<std::string>();
	std::array<int, 7> rent = j["tiles"][i][6].get<std::array<int, 7>>();

	Property tile(tile_cost, name, bank_name_, building_cost, colour, colour_type, rent);

	tiles_[i] = std::make_unique<Property>(tile);
}

void Board::InitRailroad(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int tile_cost = j["tiles"][i][2].get<int>();
	std::array<int, 4> rent = j["tiles"][i][3].get<std::array<int, 4>>();

	Railroad tile(tile_cost, name, bank_name_, rent);

	tiles_[i] = std::make_unique<Railroad>(tile);
}

void Board::InitTax(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int tax_amount = j["tiles"][i][2].get<int>();

	Tax tile(name, bank_name_, tax_amount);

	tiles_[i] = std::make_unique<Tax>(tile);
}

void Board::InitUtility(const nlohmann::json &j, const size_t i)
{
	std::string name = j["tiles"][i][1].get<std::string>();
	int tile_cost = j["tiles"][i][2].get<int>();
	std::array<int, 2> dice_multiplier = j["tiles"][i][3].get<std::array<int, 2>>();

	Utility tile(tile_cost, name, bank_name_, dice_multiplier);

	tiles_[i] = std::make_unique<Utility>(tile);
}

// Getters
std::unique_ptr<Tile>& Board::GetTileAt(const size_t i)
{
	return tiles_[i];
}

int Board::GetBoardSize() const
{
	return tiles_.size();
}

int Board::GetBailValue() const
{
	return bail_value_;
}

std::string Board::GetBankName() const
{
	return bank_name_;
}

// Operator Overloads
std::ostream& operator<<(std::ostream &os, const Board &board)
{
	int i = 1;
	for (const auto &tile : board.tiles_) {
		os << std::setw(2) << i << ". ";
		tile->Print(os);
		if (tile->GetPlayersHere().size() > 0) {
			os << termcolor::italic << termcolor::grey;
			os << "        ^ Here: ";
			for (const auto &player : tile->GetPlayersHere()) {
				os << player << " ";
			}
			os << termcolor::reset << std::endl;
		}
		++i;
	}
	return os;
}