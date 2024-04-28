#ifndef TAX_HPP
#define TAX_HPP

#include "tile.hpp"

class Tax : public Tile {
public:
	// Constructor and Destructor
	Tax(const int tile_cost, const std::string &name, const std::string &owner, const int tax_amount);
	~Tax();

	// Getters
	int GetTaxAmount() const;

	// Print
	void Print(std::ostream &os) const;
	
private:
	const int tax_amount_;
};

#endif // "TAX_HPP"