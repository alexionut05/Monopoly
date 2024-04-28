#include "dice.hpp"

// Constructor and Destructor
Dice::Dice(const int min_dice, const int max_dice)
	: min_dice_(min_dice), max_dice_(max_dice) {}

Dice::~Dice() {}

// Dice methods
std::pair<int, int> Dice::RollDice() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min_dice_, max_dice_);

	return std::make_pair(dist(gen), dist(gen));
}