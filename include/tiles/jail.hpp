#ifndef JAIl_HPP
#define JAIl_HPP

#include "tile.hpp"

class Jail : public Tile {
public:
	Jail(const std::string &name, const std::string &owner, const int jail_fine);

	int GetJailFine() const;
	
	void Print(std::ostream &os) const;
	
private:
	const int jail_fine_;
};

#endif // "JAIl_HPP"