#ifndef JAIl_HPP
#define JAIl_HPP

#include "tile.hpp"

class Jail : public Tile {
public:
	Jail(const std::string &name, const std::string &owner);

	int GetJailFine() const;

	void AddPlayerJailed(const std::string &player);
	void RemovePlayerJailed(const std::string &player);
	bool IsPlayerJailed(const std::string &player) const;
	
	void Print(std::ostream &os) const override;
	
private:
	std::vector<std::string> players_jailed_;
};

#endif // "JAIl_HPP"