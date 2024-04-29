#include "tiles/utility.hpp"

Utility::Utility(const int tile_cost, const std::string &name, const std::string &owner, const std::array<int, 2> dice_multiplier)
	: Tile(tile_cost, name, owner), tile_level_(0), dice_multiplier_(dice_multiplier) {}

int Utility::GetTileLevel() const
{
	return tile_level_;
}

std::array<int, 2> Utility::GetDiceMultiplier() const
{
	return dice_multiplier_;
}

void Utility::Print(std::ostream &os) const
{
	os << termcolor::bold << termcolor::on_grey << termcolor::color<255, 255, 255>;
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
	if (owner_ == "Bank") {
		os << " (Unowned)";
		padding = "   ";
	} else {
		os << " (" << owner_ << ")";
		padding = "";
		int padding_size = k_max_player_name_length - owner_.length();
		for (int i = 0; i < padding_size; ++i) {
			padding += " ";
		}
	}

	// Add padding equivalent for houses
	for (int i = 0; i <= k_houses_print_length; ++i) {
		padding += " ";
	}
	for (int i = 0; i < k_padding_to_cost_rent; ++i) {
		padding += " ";
	}

	os << termcolor::reset << padding;
	os << termcolor::underline;

	if (owner_ != "Bank") {
		os << "Rent: $" << dice_multiplier_.at(tile_level_) << "x Dice Roll";
	} else {
		os << "Buy for: $" << tile_cost_;
	}

	os << termcolor::reset << std::endl;
}