#ifndef JAIl_HPP
#define JAIl_HPP

#include "tile.hpp"

class Jail : public Tile {
public:
	// Constructor and Destructor
	Jail();
	~Jail();

	// Getters
	int GetJailFine() const;

private:
	const int jail_fine_ = 50;
};

#endif // "JAIl_HPP"