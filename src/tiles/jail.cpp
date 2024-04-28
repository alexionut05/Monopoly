#include "jail.hpp"

// Constructor and Destructor
Jail::Jail()
{
	owner_ = "Bank";
}

Jail::~Jail() {}

// Getters
int Jail::GetJailFine() const
{
	return jail_fine_;
}