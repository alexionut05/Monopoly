#ifndef GO_HPP
#define GO_HPP

#include "tile.hpp"

class Go : public Tile {
public:
	Go(const std::string &name, const std::string &owner, const int pass_go_amount);

	int GetPassGoAmount() const;
	
	void Reset(const std::string &bank_name) override;
	void Print(std::ostream &os) const override;
	
private:
	const int pass_go_amount_;
};

#endif // "GO_HPP"