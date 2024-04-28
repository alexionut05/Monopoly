#include "board.hpp"

// Constructor and Destructor
Board::Board() {}

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
	CardTile tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());

	tiles_[i] = std::make_unique<CardTile>(tile);
}

void Board::InitFreeParking(const nlohmann::json &j, const size_t i)
{
	FreeParking tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());

	tiles_[i] = std::make_unique<FreeParking>(tile);
}

void Board::InitGoToJail(const nlohmann::json &j, const size_t i)
{
	GoToJail tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());

	tiles_[i] = std::make_unique<GoToJail>(tile);
}

void Board::InitGo(const nlohmann::json &j, const size_t i)
{
	Go tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetPassGoAmount(j["tiles"][i][2].get<int>());

	tiles_[i] = std::make_unique<Go>(tile);
}

void Board::InitJail(const nlohmann::json &j, const size_t i)
{
	Jail tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetJailFine(j["tiles"][i][2].get<int>());

	tiles_[i] = std::make_unique<Jail>(tile);
}

void Board::InitProperty(const nlohmann::json &j, const size_t i)
{
	Property tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetTileCost(j["tiles"][i][2].get<int>());
	tile.SetBuildingCost(j["tiles"][i][3].get<int>());
	tile.SetColour(j["tiles"][i][4].get<std::string>());
	tile.SetColourType(j["tiles"][i][5].get<std::string>());
	tile.SetRent(j["tiles"][i][6].get<std::array<int, 7>>());

	tiles_[i] = std::make_unique<Property>(tile);
}

void Board::InitRailroad(const nlohmann::json &j, const size_t i)
{
	Railroad tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetTileCost(j["tiles"][i][2].get<int>());
	tile.SetRent(j["tiles"][i][3].get<std::array<int, 4>>());

	tiles_[i] = std::make_unique<Railroad>(tile);
}

void Board::InitTax(const nlohmann::json &j, const size_t i)
{
	Tax tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetTaxAmount(j["tiles"][i][2].get<int>());

	tiles_[i] = std::make_unique<Tax>(tile);
}

void Board::InitUtility(const nlohmann::json &j, const size_t i)
{
	Utility tile;
	tile.SetName(j["tiles"][i][1].get<std::string>());
	tile.SetTileCost(j["tiles"][i][2].get<int>());
	tile.SetDiceMultiplier(j["tiles"][i][3].get<std::array<int, 2>>());

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