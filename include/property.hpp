#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "tile.hpp"
#include <array>

class Property : public Tile {
public:
	// Constructor and Destructor
	Property();
	~Property();

	// Getters
	int GetTileCost() const;
	int GetBuildingCost() const;
	int GetBuildingLevel() const;
	std::array<int, 7> GetRent() const;

	// Setters
	void SetTileCost(const int tile_cost);
	void SetBuildingCost(const int building_cost);
	void SetBuildingLevel(const int building_level);
	void SetRent(const std::array<int, 7> rent);
	
private:
	int tile_cost_;
	int building_cost_;
	int building_level_;
	std::array<int, 7> rent_;
	// 0 = single tile owned
	// 1 = all colour tiles owned
	// 2 = single tile with 1 house
	// 3 = single tile with 2 houses
	// 4 = single tile with 3 houses
	// 5 = single tile with 4 houses
	// 6 = single tile with hotel
};
#endif // "PROPERTY_HPP"