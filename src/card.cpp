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

int Card::GetValue() const
{
	return value_;
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

void Card::SetValue(const int value)
{
	value_ = value;
}