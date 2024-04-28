#include "go.hpp"

// Constructor and Destructor
Go::Go()
{
	owner_ = "Bank";
}

Go::~Go() {}

// Getters
int Go::GetPassGoAmount() const
{
	return pass_go_amount_;
}