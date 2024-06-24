#ifndef TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

#include "tile.hpp"
#include "tiles/card_tile.hpp"
#include "tiles/free_parking.hpp"
#include "tiles/go_to_jail.hpp"
#include "tiles/go.hpp"
#include "tiles/jail.hpp"
#include "tiles/property.hpp"
#include "tiles/railroad.hpp"
#include "tiles/tax.hpp"
#include "tiles/utility.hpp"
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

class TileFactory {
public:
	TileFactory
		( const nlohmann::json &tile_data
		, const std::string &bank_name
		);

	std::unique_ptr<Tile> CreateTile
		( const int idx
		, const std::string &type
		);

private:
	const nlohmann::json &tile_data_;
	const std::string &bank_name_;
};

#endif // "TILE_FACTORY_HPP"