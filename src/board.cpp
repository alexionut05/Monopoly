#include "board.hpp"

Board::Board(const int bail_value, const std::string &bank_name, const std::string &tiles_file)
	: bail_value_(bail_value), bank_name_(bank_name)
{
	for (size_t i = 0; i < tiles_.size(); ++i) {
		tiles_[i] = nullptr;
	}

	std::ifstream file(tiles_file);
	if (!file.is_open()) {
		throw FileNotFound(tiles_file);
	}
	tiles_data_ = nlohmann::json::parse(file);
	file.close();
}

// Board methods
void Board::InitBoard()
{
	for (size_t i = 0; i < tiles_.size(); ++i) {
		InitTile(i);
	}
}

// Tile methods
void Board::InitTile(const size_t i)
{
	std::string type = tiles_data_["type"][i].get<std::string>();
	if (type == "Chance" || type == "Community Chest") {
		InitCardTile(i);
	} else if (type == "Free Parking") {
		InitFreeParking(i);
	} else if (type == "Go To Jail") {
		InitGoToJail(i);
	} else if (type == "Go") {
		InitGo(i);
	} else if (type == "Jail") {
		InitJail(i);
	} else if (type == "Property") {
		InitProperty(i);
	} else if (type == "Railroad") {
		InitRailroad(i);
	} else if (type == "Tax") {
		InitTax(i);
	} else if (type == "Utility") {
		InitUtility(i);
	}
}

void Board::InitCardTile(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();

	CardTile tile(name, bank_name_);

	tiles_[i] = std::make_unique<CardTile>(tile);
}

void Board::InitFreeParking(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();

	FreeParking tile(name, bank_name_);

	tiles_[i] = std::make_unique<FreeParking>(tile);
}

void Board::InitGoToJail(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();

	GoToJail tile(name, bank_name_);

	tiles_[i] = std::make_unique<GoToJail>(tile);
}

void Board::InitGo(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();
	int pass_go = tiles_data_["tile_price"][i].get<int>();

	Go tile(name, bank_name_, pass_go);

	tiles_[i] = std::make_unique<Go>(tile);
}

void Board::InitJail(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();

	Jail tile(name, bank_name_);

	tiles_[i] = std::make_unique<Jail>(tile);
}

void Board::InitProperty(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();
	int tile_cost = tiles_data_["tile_price"][i].get<int>();
	int building_cost = tiles_data_["house_price"][i].get<int>();
	std::string colour = tiles_data_["colour"][i].get<std::string>();
	std::string colour_type = tiles_data_["colour_type"][i].get<std::string>();
	std::array<int, 7> rent = tiles_data_["rents"][i].get<std::array<int, 7>>();

	Property tile(tile_cost, name, bank_name_, building_cost, colour, colour_type, rent);

	tiles_[i] = std::make_unique<Property>(tile);
}

void Board::InitRailroad(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();
	int tile_cost = tiles_data_["tile_price"][i].get<int>();
	std::array<int, 4> rent = tiles_data_["rents"][i].get<std::array<int, 4>>();

	Railroad tile(tile_cost, name, bank_name_, rent);

	tiles_[i] = std::make_unique<Railroad>(tile);
}

void Board::InitTax(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();
	int tax_amount = tiles_data_["tile_price"][i].get<int>();

	Tax tile(name, bank_name_, tax_amount);

	tiles_[i] = std::make_unique<Tax>(tile);
}

void Board::InitUtility(const size_t i)
{
	std::string name = tiles_data_["name"][i].get<std::string>();
	int tile_cost = tiles_data_["tile_price"][i].get<int>();
	std::array<int, 2> dice_multiplier = tiles_data_["rents"][i].get<std::array<int, 2>>();

	Utility tile(tile_cost, name, bank_name_, dice_multiplier);

	tiles_[i] = std::make_unique<Utility>(tile);
}

// Getters
std::unique_ptr<Tile>& Board::GetTileAt(const size_t i)
{
	return tiles_[i];
}

size_t Board::GetBoardSize() const
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
			os << termcolor::italic << termcolor::white;
			os << "        ^ Here: ";
			for (const auto &player : tile->GetPlayersHere()) {
				if (dynamic_cast<Jail*>(tile.get())) {
					Jail *jail = dynamic_cast<Jail*>(tile.get());
					if (jail->IsPlayerJailed(player)) {
						os << termcolor::red << player << termcolor::grey << "  ";
					} else {
						os << player << " (visiting)  ";
					}
				} else {
					os << player << "  ";
				}
			}
			os << termcolor::reset << std::endl;
		}
		++i;
	}
	return os;
}
