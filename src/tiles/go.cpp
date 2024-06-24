#include "tiles/go.hpp"

Go::Go(const std::string &name, const std::string &owner, const int pass_go_amount)
	: Tile(0, name, owner), pass_go_amount_(pass_go_amount) {}

int Go::GetPassGoAmount() const
{
	return pass_go_amount_;
}

void Go::Reset(const std::string &bank_name)
{
	owner_ = bank_name;
}

void Go::Print(std::ostream &os) const
{
	os << termcolor::bold << termcolor::on_color<0, 0, 0>;
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
	os << std::endl;
}