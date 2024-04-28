#include "tile.hpp"

// Constructor and Destructor
Tile::Tile() {}

Tile::~Tile() {}

// Getters
int Tile::GetTileCost() const
{
	return tile_cost_;
}

std::string Tile::GetName() const
{
	return name_;
}

std::string Tile::GetOwner() const
{
	return owner_;
}

std::vector<std::string> Tile::GetPlayersHere() const
{
	return players_here_;
}

// Setters
void Tile::SetName(const std::string name)
{
	name_ = name;
}

void Tile::SetOwner(const std::string owner)
{
	owner_ = owner;
}

void Tile::SetPlayersHere(const std::vector<std::string> players_here)
{
	players_here_ = players_here;
}

// Methods
void Tile::AddPlayerHere(const std::string player_name)
{
	players_here_.push_back(player_name);
}

void Tile::RemovePlayerHere(const std::string player_name)
{
	players_here_.erase(std::remove(players_here_.begin(), players_here_.end(), player_name), players_here_.end());
}

// Print
void Tile::Print(std::ostream &os) const
{
	os << " Wtf? This isn't supposed to happen!" << std::endl;
}
