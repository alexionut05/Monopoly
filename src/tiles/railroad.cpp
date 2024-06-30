#include "tiles/railroad.hpp"

Railroad::Railroad(const int tile_cost, const std::string &name, const std::string &owner, const std::array<int, 4> rent)
	: Tile(tile_cost, name, owner), tile_level_(0), rent_(rent) {}

int Railroad::GetTileLevel() const
{
	return tile_level_;
}

std::array<int, 4> Railroad::GetRent() const
{
	return rent_;
}

void Railroad::SetTileLevel(const int level)
{
	tile_level_ = level;
}

void Railroad::Reset(const std::string &bank_name)
{
	owner_ = bank_name;
	tile_level_ = 0;
}

void Railroad::Print(std::ostream &os) const
{
	os << termcolor::bold << termcolor::on_white << termcolor::color<255, 255, 255>;
	std::string padding_left = " ";
	int padding_left_size = (k_max_tile_name_length - name_.length()) / 2;
	for (int i = 0; i < padding_left_size; i++) {
		padding_left += " ";
	}
	std::string padding_right = " ";
	int padding_right_size = k_max_tile_name_length - name_.length() - padding_left_size;
	for (int i = 0; i < padding_right_size; i++) {
		padding_right += " ";
	}
	os << padding_left << name_ << padding_right;
	os << termcolor::reset;

	std::string padding = "";
	os << termcolor::italic;
	if (GetOwner() == "Bank") {
		os << " (Unowned)";
		padding = "   ";
	} else {
		os << " (" << GetOwner() << ")";
		padding = "";
		int padding_size  = k_max_player_name_length - owner_.length();
		for (int i = 0; i < padding_size; ++i) {
			padding += " ";
		}
	}

	// Add padding equivalent to houses
	for (int i = 0; i <= k_houses_print_length; ++i) {
		padding += " ";
	}
	for (int i = 0; i < k_padding_to_cost_rent; ++i) {
		padding += " ";
	}

	os << termcolor::reset << padding;

	os << termcolor::underline;

	if (GetOwner() != "Bank") {
		os << "Rent: $" << GetRent().at(GetTileLevel());
	} else {
		os << "Buy for: $" << GetTileCost();
	}

	os << termcolor::reset << std::endl;
}

bool Railroad::IsPlayerEnabledTile() const
{
	return true;
}