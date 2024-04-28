#include "deck.hpp"

// Constructors and Destructor
Deck::Deck() {}

Deck::Deck(const std::string &language, const std::string &deck_type, const int cards_count)
{
	std::ifstream file("../locales/" + language + "/" + deck_type + "_card.json");
	file >> deck_data_;
	file.close();
	cards_count_ = cards_count;
}

Deck::~Deck() {}

// Deck methods
void Deck::InitDeck()
{
	for (int i = 0; i < cards_count_; ++i) {
		Card new_card;
		new_card.SetDescription(deck_data_["description"][i].get<std::string>());
		new_card.SetType(deck_data_["type"][i].get<std::string>());
		new_card.SetValues(std::make_pair(deck_data_["value1"][i].get<int>(), deck_data_["value2"][i].get<int>()));
	}

	ShuffleDeck();
}

void Deck::ShuffleDeck()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards_.begin(), cards_.end(), g);
}

Card Deck::DrawCard()
{
	Card card = cards_.back();
	cards_.pop_back();

	if (cards_.empty()) {
		InitDeck();
	}

	return card;
}