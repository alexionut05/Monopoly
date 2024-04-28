#ifndef DICE_HPP
#define DICE_HPP

#include <random>

class Dice {
public:
	// Constructor and Destructor
	Dice(const int min_dice, const int max_dice);
	~Dice();

	// Dice methods
	std::pair<int, int> RollDice() const;

private:
	const int min_dice_;
	const int max_dice_;
};

#endif // "DICE_HPP"