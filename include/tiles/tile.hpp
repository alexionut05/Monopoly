#ifndef TILE_HPP
#define TILE_HPP

#include <array>
#include <string>

class Tile {
public:
	// Constructor and Destructor
	Tile();
	virtual ~Tile();

	// Getters
	std::string GetName() const;
	std::string GetType() const;
	std::string GetColour() const;
	std::string GetOwner() const;

	// Setters
	void SetName(const std::string name);
	void SetOwner(const std::string owner);

	// Methods
	void TransferOwnership(const std::string new_owner);

protected:
	std::string name_;
	std::string owner_;
};

#endif // "TILE_HPP"