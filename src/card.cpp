#include "card.hpp"

// Constructor and Destructor (pt tema 1)
Card::Card() : description_(""), type_(""), values_(std::make_pair(0, 0)) {}

Card::Card(const std::string &description, const std::string &type, const std::pair<int, int> &values)
	: description_(description), type_(type), values_(values) {}

Card::Card(const Card &other)
	: description_(other.description_), type_(other.type_), values_(other.values_) {}

Card::~Card() {}

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

void Card::swap(Card &other) noexcept
{
	std::swap(const_cast<std::string&>(description_), const_cast<std::string&>(other.description_));
	std::swap(const_cast<std::string&>(type_), const_cast<std::string&>(other.type_));
	std::swap(const_cast<std::pair<int, int>&>(values_), const_cast<std::pair<int, int>&>(other.values_));
}

Card &Card::operator=(const Card &other)
{
	swap(const_cast<Card&>(other));

	return *this;
}

// pt tema 1
std::ostream &operator<<(std::ostream &out, const Card &card)
{
	out << card.description_ << " " << card.type_ << " " << card.values_.first << " " << card.values_.second;

	return out;
}

// asa s-ar face daca nu erau const, dar as dori sa le pastrez const
// le las just in case
//
// void std::swap(Card &first, Card &second) noexcept
// {
// 	std::swap(first.description_, second.description_);
// 	std::swap(first.type_, second.type_);
// 	std::swap(first.values_, second.values_);
// }