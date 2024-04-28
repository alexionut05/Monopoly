#include "tile.hpp"

// Constructor and Destructor
Tile::Tile() {}

Tile::~Tile() {}

// Getters
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

// Print
void Tile::Print(std::ostream &os) const
{
	os << " Wtf? This isn't supposed to happen!" << std::endl;
}

