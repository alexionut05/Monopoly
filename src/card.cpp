#include "card.hpp"

// Constructor and Destructor
Card::Card() {}

Card::~Card() {}

// Getters
std::string Card::GetDescription() const
{
	return description_;
}

std::string Card::GetType() const
{
	return type_;
}

std::pair<int, int> Card::GetValue() const
{
	return values_;
}

// Setters
void Card::SetDescription(const std::string &description)
{
	description_ = description;
}

void Card::SetType(const std::string &type)
{
	type_ = type;
}

void Card::SetValues(const std::pair<int, int> &values)
{
	values_ = values;
}