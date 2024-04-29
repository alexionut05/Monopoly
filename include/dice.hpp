#ifndef DICE_HPP
#define DICE_HPP

#include <random>

class Dice {
public:
	Dice(const int min_dice, const int max_dice);

	std::pair<int, int> RollDice() const;

private:
	const int min_dice_;
	const int max_dice_;
};

#endif // "DICE_HPP"