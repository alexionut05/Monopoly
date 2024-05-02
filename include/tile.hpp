#ifndef TILE_HPP
#define TILE_HPP

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <termcolor/termcolor.hpp>

class Tile {
public:
	Tile(const int tile_cost, const std::string name, const std::string owner);
	virtual ~Tile();

	int GetTileCost() const;
	std::string GetName() const;
	std::string GetOwner() const;
	std::vector<std::string> GetPlayersHere() const;

	void SetOwner(const std::string &owner);

	void AddPlayerHere(const std::string &player_name);
	void RemovePlayerHere(const std::string &player_name);

	virtual void Print(std::ostream &os) const = 0;

	friend std::ostream &operator<<(std::ostream &out, const Tile &tile);

protected:
	int tile_cost_;
	std::string name_;
	std::string owner_;
	std::vector<std::string> players_here_;

	// Hard coded values for padding
	const int k_max_tile_name_length = 30;
	const int k_max_player_name_length = 10; // defined in game.hpp too - not ideal
	const int k_houses_print_length = 20;
	const int k_padding_to_cost_rent = 10;
};

#endif // "TILE_HPP"