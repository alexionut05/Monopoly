#include "tile.hpp"

// Constructor and Destructor
Tile::Tile() {}

Tile::~Tile() {}

// Getters
std::string Tile::GetName() const
{
	return name_;
}

std::string Tile::GetType() const
{
	return type_;
}

std::string Tile::GetColour() const
{
	return colour_;
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

void Tile::SetType(const std::string type)
{
	type_ = type;
}

void Tile::SetColour(const std::string colour)
{
	colour_ = colour;
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