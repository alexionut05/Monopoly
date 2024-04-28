#ifndef JAIl_HPP
#define JAIl_HPP

#include "tile.hpp"
#include <iostream>

class Jail : public Tile {
public:
	// Constructor and Destructor
	Jail();
	~Jail();

	// Getters
	int GetJailFine() const;

	// Setters
	void SetJailFine(const int jail_fine);

	// Print
	void Print(std::ostream &os) const;
	
private:
	int jail_fine_;
};

#endif // "JAIl_HPP"