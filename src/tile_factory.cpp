#include "tile_factory.hpp"

std::unique_ptr<Tile> TileFactory::CreateTile
	( const int idx
	, const std::string &type
	, const nlohmann::json &tile_data
	, const std::string &bank_name )
{
	std::unique_ptr<Tile> tile = nullptr;
	std::string name = tile_data["name"][idx].get<std::string>();

	if (type == "Chance" || type == "Community Chest") {
		tile = std::make_unique<CardTile>(name, bank_name);
	} else if (type == "Free Parking") {
		tile = std::make_unique<FreeParking>(name, bank_name);
	} else if (type == "Go To Jail") {
		tile = std::make_unique<GoToJail>(name, bank_name);
	} else if (type == "Go") {
		int pass_go_amount = tile_data["tile_price"][idx].get<int>();
		tile = std::make_unique<Go>(name, bank_name, pass_go_amount);
	} else if (type == "Jail") {
		tile = std::make_unique<Jail>(name, bank_name);
	} else if (type == "Property") {
		int tile_cost = tile_data["tile_price"][idx].get<int>();
		int building_cost = tile_data["house_price"][idx].get<int>();
		std::string colour = tile_data["colour"][idx].get<std::string>();
		std::string colour_type = tile_data["colour_type"][idx].get<std::string>();
		std::array<int, 7> rent = tile_data["rents"][idx].get<std::array<int, 7>>();
		tile = std::make_unique<Property>(tile_cost, name, bank_name, building_cost, colour, colour_type, rent);
	} else if (type == "Railroad") {
		int tile_cost = tile_data["tile_price"][idx].get<int>();
		std::array<int, 4> rent = tile_data["rents"][idx].get<std::array<int, 4>>();
		tile = std::make_unique<Railroad>(tile_cost, name, bank_name, rent);
	} else if (type == "Tax") {
		int tax_amount = tile_data["tile_price"][idx].get<int>();
		tile = std::make_unique<Tax>(name, bank_name, tax_amount);
	} else if (type == "Utility") {
		int tile_cost = tile_data["tile_price"][idx].get<int>();
		std::array<int, 2> dice_multiplier = tile_data["rents"][idx].get<std::array<int, 2>>();
		tile = std::make_unique<Utility>(tile_cost, name, bank_name, dice_multiplier);
	}
	
	return tile;
}