#ifndef DECK_HPP
#define DECK_HPP\

#include "card.hpp"
#include <fstream>
#include <random>
#include <vector>
#include "json.hpp"

class Deck {
public:
	// Constructors and Destructor
	Deck();
	Deck(const std::string &language, const std::string &deck_type, const int cards_count);
	~Deck();

	// Deck methods
	void InitDeck();
	void ShuffleDeck();
	Card DrawCard();

private:
	std::vector<Card> cards_;
	nlohmann::json deck_data_;
	int cards_count_;
};

#endif // "DECK_HPP"