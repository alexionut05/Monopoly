#include "tax.hpp"

// Constructor and Destructor
Tax::Tax()
{
	owner_ = "Bank";
}

Tax::~Tax() {}

// Getters
int Tax::GetTaxAmount() const
{
	return tax_amount_;
}

// Setters
void Tax::SetTaxAmount(const int tax_amount)
{
	tax_amount_ = tax_amount;
}