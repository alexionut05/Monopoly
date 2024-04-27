#ifndef TILE_HPP
#define TILE_HPP

#include <array>
#include <string>

class Tile {
public:
	// Constructor and Destructor
	Tile();
	~Tile();

	// Getters
	std::string GetName() const;
	std::string GetType() const;
	std::string GetColour() const;
	std::string GetOwner() const;
	int GetTilePrice() const;
	int GetPropertyPrice() const;
	std::array<int, 7> GetRents() const;

	// Setters
	void SetName(const std::string name);
	void SetType(const std::string type);
	void SetColour(const std::string colour);
	void SetOwner(const std::string owner);
	void SetTilePrice(const int tile_price);
	void SetPropertyPrice(const int property_price);
	void SetRents(const std::array<int, 7> rents);

private:
	std::string name_;
	std::string type_;
	std::string colour_;
	std::string owner_;
	int tile_price_;
	int property_price_;
	std::array<int, 7> rents_;
	// 0 = owned tile
	// 1 = owned all colour tiles
	// 2 = owned all colour tiles and 1 house
	// 3 = owned all colour tiles and 2 houses
	// 4 = owned all colour tiles and 3 houses
	// 5 = owned all colour tiles and 4 houses
	// 6 = owned all colour tiles and 1 hotel
};

#endif // "TILE_HPP"