#include "tiles/railroad.hpp"

// Constructor and Destructor
Railroad::Railroad()
{
	owner_ = "Bank";
}

Railroad::~Railroad() {}

// Getters
int Railroad::GetTileCost() const
{
	return tile_cost_;
}

int Railroad::GetTileLevel() const
{
	return tile_level_;
}

std::array<int, 4> Railroad::GetRent() const
{
	return rent_;
}

// Setters
void Railroad::SetTileCost(const int tile_cost)
{
	tile_cost_ = tile_cost;
}

void Railroad::SetTileLevel(const int tile_level)
{
	tile_level_ = tile_level;
}

void Railroad::SetRent(const std::array<int, 4> rent)
{
	rent_ = rent;
}

// Print
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
		os << "Rent: " << GetRent().at(GetTileLevel());
	} else {
		os << "Buy for: $" << GetTileCost();
	}

	os << termcolor::reset << std::endl;
}