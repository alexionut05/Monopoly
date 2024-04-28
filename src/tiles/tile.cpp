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

// Setters
void Tile::SetName(const std::string name)
{
	name_ = name;
}

void Tile::SetOwner(const std::string owner)
{
	owner_ = owner;
}

// Methods
void Tile::TransferOwnership(const std::string new_owner)
{
	owner_ = new_owner;
}