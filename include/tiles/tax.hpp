#ifndef TAX_HPP
#define TAX_HPP

#include "tile.hpp"

class Tax : public Tile {
public:
	Tax(const std::string &name, const std::string &owner, const int tax_amount);
	
	int GetTaxAmount() const;

	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;
	
private:
	const int tax_amount_;
};

#endif // "TAX_HPP"