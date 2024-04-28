#include "deck.hpp"

// Constructors and Destructor
Deck::Deck(const std::string &language, const std::string &deck_type, const int cards_count)
	: cards_count_(cards_count)
{
	std::ifstream file("data/" + language + "/" + deck_type + ".json");
	file >> deck_data_;
	file.close();
}

Deck::~Deck() {}

// Deck methods
void Deck::InitDeck()
{
	for (int i = 0; i < cards_count_; ++i) {
		std::string description = deck_data_["description"][i].get<std::string>();
		std::string type = deck_data_["type"][i].get<std::string>();
		std::pair<int, int> values = std::make_pair(deck_data_["value1"][i].get<int>(), deck_data_["value2"][i].get<int>());

		Card new_card(description, type, values);

		cards_.push_back(new_card);
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