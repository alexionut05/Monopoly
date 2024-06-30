#include "tiles/jail.hpp"

Jail::Jail(const std::string &name, const std::string &owner)
	: Tile(0, name, owner) {}

void Jail::AddPlayerJailed(const std::string &player)
{
	players_jailed_.push_back(player);
}

bool Jail::IsPlayerJailed(const std::string &player) const
{
	return std::find(players_jailed_.begin(), players_jailed_.end(), player) != players_jailed_.end();
}

void Jail::Reset(const std::string &bank_name)
{
	owner_ = bank_name;
	players_jailed_.clear();
}

void Jail::Print(std::ostream &os) const
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
	os << std::endl;
}

void Jail::RemovePlayerJailed(const std::string &player)
{
	players_jailed_.erase(std::remove(players_jailed_.begin(), players_jailed_.end(), player), players_jailed_.end());
}