#ifndef GO_TO_JAIL_HPP
#define GO_TO_JAIL_HPP

#include "tile.hpp"

class GoToJail : public Tile {
public:
	GoToJail(const std::string &name, const std::string &owner);
	
	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;
};

#endif // "GO_TO_JAIL_HPP"