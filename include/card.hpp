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
	int GetValue() const;

	// Setters
	void SetDescription(const std::string &description);
	void SetType(const std::string &type);
	void SetValue(const int value);
private:
	std::string description_;
	std::string type_;
	int value_;
};

#endif // "CARD_HPP"