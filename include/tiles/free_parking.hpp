#ifndef FREE_PARKING_HPP
#define FREE_PARKING_HPP

#include "tile.hpp"

class FreeParking : public Tile {
public:
	FreeParking(const std::string &name, const std::string &owner);
	
	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;
};

#endif // "FREE_PARKING_HPP"