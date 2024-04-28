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
	void SetType(const std::string type);
	void SetColour(const std::string colour);
	void SetOwner(const std::string owner);

protected:
	std::string name_;
	std::string type_;
	std::string colour_;
	std::string owner_;
};

#endif // "TILE_HPP"