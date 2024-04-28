#ifndef TAX_HPP
#define TAX_HPP

#include "tile.hpp"

class Tax : public Tile {
public:
	// Constructor and Destructor
	Tax();
	~Tax();

	// Getters
	int GetTaxAmount() const;

	// Setters
	void SetTaxAmount(const int tax_amount);
	
private:
	int tax_amount_;
};

#endif // "TAX_HPP"