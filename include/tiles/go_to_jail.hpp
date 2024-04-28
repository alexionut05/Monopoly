#ifndef GO_TO_JAIL_HPP
#define GO_TO_JAIL_HPP

#include "tile.hpp"

class GoToJail : public Tile {
public:
	// Constructor and Destructor
	GoToJail(const std::string &name, const std::string &owner);
	~GoToJail();

	// Print
	void Print(std::ostream &os) const;
};

#endif // "GO_TO_JAIL_HPP"