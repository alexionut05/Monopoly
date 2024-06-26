#include "dice.hpp"

Dice::Dice(const int min_dice, const int max_dice)
	: min_dice_(min_dice), max_dice_(max_dice) {}

std::pair<int, int> Dice::RollDice() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min_dice_, max_dice_);

	return std::make_pair(dist(gen), dist(gen));
}

// pt tema 1
std::ostream &operator<<(std::ostream &out, const Dice &dice)
{
	out << dice.min_dice_ << " " << dice.max_dice_;

	return out;
}