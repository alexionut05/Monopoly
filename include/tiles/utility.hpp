#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "tile.hpp"

class Utility : public Tile {
public:
	Utility(const int tile_cost, const std::string &name, const std::string &owner, const std::array<int, 2> dice_multiplier);

	int GetTileLevel() const;
	std::array<int, 2> GetDiceMultiplier() const;

	void SetTileLevel(const int level);

	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;

	// Tile specific functions
	bool IsPlayerEnabledTile() const override;

private:
	int tile_level_;
	const std::array<int, 2> dice_multiplier_;
};

#endif // "UTILITY_HPP"