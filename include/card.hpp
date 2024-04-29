#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
public:
	// Constructors and Destructor (pt tema 1)
	Card(const std::string &description, const std::string &type, const std::pair<int, int> &values);
	Card(const Card &other);
	~Card();

	std::string GetDescription() const;
	std::string GetType() const;
	std::pair<int, int> GetValue() const;

	Card &operator=(const Card &other);

private:
	const std::string description_;
	const std::string type_;
	const std::pair<int, int> values_;
};

#endif // "CARD_HPP"