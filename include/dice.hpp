#ifndef DICE_HPP
#define DICE_HPP

#include <random>

class Dice {
public:
	// Constructor and Destructor
	Dice();
	~Dice();

	// Dice methods
	std::pair<int, int> RollDice() const;

private:
	const int min_dice_ = 1;
	const int max_dice_ = 6;
};

#endif // "DICE_HPP"