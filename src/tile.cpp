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

int Tile::GetTilePrice() const
{
	return tile_price_;
}

int Tile::GetPropertyPrice() const
{
	return property_price_;
}

std::array<int, 7> Tile::GetRents() const
{
	return rents_;
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

void Tile::SetTilePrice(const int tile_price)
{
	tile_price_ = tile_price;
}

void Tile::SetPropertyPrice(const int property_price)
{
	property_price_ = property_price;
}

void Tile::SetRents(const std::array<int, 7> rents)
{
	rents_ = rents;
}