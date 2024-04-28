#include "card.hpp"

// Constructor and Destructor
Card::Card(const std::string &description, const std::string &type, const std::pair<int, int> &values)
	: description_(description), type_(type), values_(values) {}

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

// Operator Overloads
Card &Card::operator=(const Card &other)
{
	if (this != &other) {
		const_cast<std::string&>(description_) = other.description_;
		const_cast<std::string&>(type_) = other.type_;
		const_cast<std::pair<int, int>&>(values_) = other.values_;
	}

	return *this;
}