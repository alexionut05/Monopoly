#include "tiles/tax.hpp"

// Constructor and Destructor
Tax::Tax(const int tile_cost, const std::string &name, const std::string &owner, const int tax_amount)
	: Tile(tile_cost, name, owner), tax_amount_(tax_amount) {}

Tax::~Tax() {}

// Getters
int Tax::GetTaxAmount() const
{
	return tax_amount_;
}

// Print
void Tax::Print(std::ostream &os) const
{
	os << termcolor::on_color<0, 0, 0> << termcolor::bold;
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
	os << " " << termcolor::italic << "($" << tax_amount_ << ")";
	os << termcolor::reset;
	os << std::endl;
}