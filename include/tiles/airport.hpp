#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include "tile.hpp"

// Airports are a tile prototype that would be allowed
// to be purchased by players, similarly to properties.
// Airports have a base rent, depening on the number of
// airports owned by the player (similar to railroads).
// Upon landing on their own airport, and if all airports
// are owned by them, the player is allowed to try to roll
// for a double, to get to the next airport.
//
// Due to the nature of the code, the logic will have to be
// handled in the game class, however the airport class
// will handle what it can handle, such as the property, railroad
// and utility subclasses.
//
// Additionally, it would have to be added in CMakelists.txt

class Airport : public Tile {
public:
	Airport
		( const int tile_cost
		, const std::string &name
		, const std::string &owner
		, const std::array<int, 4> rent
		);

	int GetTileLevel() const;
	std::array<int, 4> GetRent() const;

	void SetTileLevel(const int tile_level);

	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;

private:
	int tile_level_;
	const std::array<int, 4> rent_;
};

#endif // "AIRPORT_HPP"