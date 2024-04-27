#include "board.hpp"

// Constructor and Destructor
Board::Board() {}

Board::~Board() {}

// Board methods
void Board::InitBoard(const std::string &language)
{
	// Load tiles
	std::ifstream file("../locales/" + language + "/tiles.json");
	nlohmann::json tiles_json = nlohmann::json::parse(file);
	file.close();

	// Init tiles
	int i = 0;
	for (Tile &tile : tiles_) {
		tile.SetName(tiles_json["tile_names"][i]);
		tile.SetType(tiles_json["tile_types"][i]);
		tile.SetColour(tiles_json["tile_colours"][i]);
		tile.SetTilePrice(tiles_json["tile_prices"][i]);
		tile.SetPropertyPrice(tiles_json["tile_property_costs"][i]);
		tile.SetRents(tiles_json["tile_rent_costs"][i]);
		i++;
	}
}