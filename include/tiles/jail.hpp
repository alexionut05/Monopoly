#ifndef JAIl_HPP
#define JAIl_HPP

#include "tile.hpp"

class Jail : public Tile {
public:
	// Constructor and Destructor
	Jail(const std::string &name, const std::string &owner, const int jail_fine);
	~Jail();

	// Getters
	int GetJailFine() const;

	// Print
	void Print(std::ostream &os) const;
	
private:
	const int jail_fine_;
};

#endif // "JAIl_HPP"