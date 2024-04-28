#include "property.hpp"

// Constructor and Destructor
Property::Property()
{
	building_level_ = 0;
	owner_ = "Bank";
}

Property::~Property() {}

// Getters
int Property::GetTileCost() const
{
	return tile_cost_;
}

int Property::GetBuildingCost() const
{
	return building_cost_;
}

int Property::GetBuildingLevel() const
{
	return building_level_;
}

std::array<int, 7> Property::GetRent() const
{
	return rent_;
}

// Setters
void Property::SetTileCost(const int tile_cost)
{
	tile_cost_ = tile_cost;
}

void Property::SetBuildingCost(const int building_cost)
{
	building_cost_ = building_cost;
}

void Property::SetBuildingLevel(const int building_level)
{
	building_level_ = building_level;
}

void Property::SetRent(const std::array<int, 7> rent)
{
	rent_ = rent;
}