#include "railroad.hpp"

// Constructor and Destructor
Railroad::Railroad()
{
	owner_ = "Bank";
}

Railroad::~Railroad() {}

// Getters
int Railroad::GetTileCost() const
{
	return tile_cost_;
}

std::array<int, 4> Railroad::GetRent() const
{
	return rent_;
}