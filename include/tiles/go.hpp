#ifndef GO_HPP
#define GO_HPP

#include "tile.hpp"

class Go : public Tile {
public:
	// Constructor and Destructor
	Go();
	~Go();

	// Getters
	int GetPassGoAmount() const;

private:
	const int pass_go_amount_ = 200;
};

#endif // "GO_HPP"