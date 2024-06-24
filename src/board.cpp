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
	TileFactory tile_factory(tiles_data_, bank_name_);
	for (size_t i = 0; i < tiles_.size(); ++i) {
		std::string type = tiles_data_["type"][i].get<std::string>();
		tiles_[i] = tile_factory.CreateTile(i, type);
	}
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
			os << termcolor::italic << termcolor::grey;
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