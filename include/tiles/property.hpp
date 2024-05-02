#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "tile.hpp"

enum {
	BROWN_R = 165,
	BROWN_G = 42,
	BROWN_B = 42,
	LIGHT_BLUE_R = 128,
	LIGHT_BLUE_G = 204,
	LIGHT_BLUE_B = 255,
	PINK_R = 255,
	PINK_G = 105,
	PINK_B = 180,
	ORANGE_R = 255,
	ORANGE_G = 128,
	ORANGE_B = 0,
	RED_R = 255,
	RED_G = 0,
	RED_B = 0,
	YELLOW_R = 255,
	YELLOW_G = 255,
	YELLOW_B = 0,
	GREEN_R = 0,
	GREEN_G = 128,
	GREEN_B = 0,
	BLUE_R = 0,
	BLUE_G = 0,
	BLUE_B = 255
};

class Property : public Tile {
public:
	Property(const int tile_cost,  const std::string &name, const std::string &owner,
		const int building_cost, const std::string &colour, const std::string &colour_type, const std::array<int, 7> rent);
		
	int GetBuildingCost() const;
	int GetTileLevel() const;
	std::string GetColour() const;
	std::string GetColourType() const;
	std::array<int, 7> GetRent() const;

	void AddBuilding(const int amount = 1);
	void SetTileLevel(const int level);

	void Print(std::ostream &os) const;
	void SetPrintColour(std::ostream &os) const;

private:
	const int building_cost_;
	int tile_level_;
	const std::string colour_;
	const std::string colour_type_;
	const std::array<int, 7> rent_;
	// 0 = single tile owned
	// 1 = all colour tiles owned
	// 2 = single tile with 1 house
	// 3 = single tile with 2 houses
	// 4 = single tile with 3 houses
	// 5 = single tile with 4 houses
	// 6 = single tile with hotel
	// !pare redundant sa avem culoarea si ca nume, insa o pastrez pt accesibilitate
	// !voi implementa mai tarziu
};
#endif // "PROPERTY_HPP"