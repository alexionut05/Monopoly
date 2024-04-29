#ifndef DECK_HPP
#define DECK_HPP\

#include "card.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <nlohmann/json.hpp>

class Deck {
public:
	Deck(const std::string &language, const std::string &deck_type, const int cards_count);

	void InitDeck();
	void ShuffleDeck();
	Card DrawCard();

	friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

private:
	std::vector<Card> cards_;
	nlohmann::json deck_data_;
	const int cards_count_;
};

#endif // "DECK_HPP"