#ifndef GO_TO_JAIL_HPP
#define GO_TO_JAIL_HPP

#include "tile.hpp"
#include <iostream>

class GoToJail : public Tile {
public:
	// Constructor and Destructor
	GoToJail();
	~GoToJail();

	// Print
	void Print(std::ostream &os) const;
};

#endif // "GO_TO_JAIL_HPP"