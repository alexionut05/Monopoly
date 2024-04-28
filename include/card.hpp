#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
public:
	// Constructor and Destructor
	Card();
	~Card();

	// Getters
	std::string GetDescription() const;
	std::string GetType() const;
	std::pair<int, int> GetValue() const;

	// Setters
	void SetDescription(const std::string &description);
	void SetType(const std::string &type);
	void SetValues(const std::pair<int, int> &values);

private:
	std::string description_;
	std::string type_;
	std::pair<int, int> values_;
};

#endif // "CARD_HPP"