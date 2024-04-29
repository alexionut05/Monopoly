#ifndef GO_HPP
#define GO_HPP

#include "tile.hpp"

class Go : public Tile {
public:
	Go(const std::string &name, const std::string &owner, const int pass_go_amount);

	int GetPassGoAmount() const;
	
	void Print(std::ostream &os) const;
	
private:
	const int pass_go_amount_;
};

#endif // "GO_HPP"