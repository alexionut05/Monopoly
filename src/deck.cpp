#include "deck.hpp"

// Constructors and Destructor
Deck::Deck() {}

Deck::Deck(const std::string &language, const std::string &deck_type)
{
	std::ifstream file("../locales/" + language + "/" + deck_type + "_card.json");
	file >> deck_data_;
	file.close();
}

Deck::~Deck() {}

// Deck methods
void Deck::InitDeck()
{
	for (const auto &card : deck_data_)
	{
		Card new_card;
		new_card.SetDescription(card["description"].get<std::string>());
		new_card.SetType(card["type"].get<std::string>());
		new_card.SetValues(std::make_pair<int, int>(card["values1"].get<int>(), card["values2"].get<int>()));
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