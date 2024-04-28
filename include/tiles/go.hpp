#ifndef GO_HPP
#define GO_HPP

#include "tile.hpp"
#include <iostream>

class Go : public Tile {
public:
	// Constructor and Destructor
	Go();
	~Go();

	// Getters
	int GetPassGoAmount() const;

	// Setters
	void SetPassGoAmount(const int pass_go_amount);

	// Print
	void Print(std::ostream &os) const;
	
private:
	int pass_go_amount_;
};

#endif // "GO_HPP"