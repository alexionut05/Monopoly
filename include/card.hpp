#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
public:
	// Constructor and Destructor
	Card(const std::string &description, const std::string &type, const std::pair<int, int> &values);
	~Card();

	// Getters
	std::string GetDescription() const;
	std::string GetType() const;
	std::pair<int, int> GetValue() const;

	// Operator Overloads
	Card &operator=(const Card &other);

private:
	const std::string description_;
	const std::string type_;
	const std::pair<int, int> values_;
};

#endif // "CARD_HPP"