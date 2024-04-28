#include "tiles/property.hpp"

// Constructor and Destructor
Property::Property()
{
	tile_level_ = 0;
	owner_ = "Bank";
}

Property::~Property() {}

// Getters
int Property::GetBuildingCost() const
{
	return building_cost_;
}

int Property::GetTileLevel() const
{
	return tile_level_;
}

std::string Property::GetColour() const
{
	return colour_;
}

std::string Property::GetColourType() const
{
	return colour_type_;
}

std::array<int, 7> Property::GetRent() const
{
	return rent_;
}

// Setters
void Property::SetTileCost(const int tile_cost)
{
	tile_cost_ = tile_cost;
}

void Property::SetBuildingCost(const int building_cost)
{
	building_cost_ = building_cost;
}

void Property::SetTileLevel(const int tile_level)
{
	tile_level_ = tile_level;
}

void Property::SetColour(const std::string colour)
{
	colour_ = colour;
}

void Property::SetColourType(const std::string colour_type)
{
	colour_type_ = colour_type;
}

void Property::SetRent(const std::array<int, 7> rent)
{
	rent_ = rent;
}

// Print
void Property::Print(std::ostream &os) const
{
	os << termcolor::bold;
	if (colour_type_ == "Brown") {
		os << termcolor::on_color<BROWN_R, BROWN_G, BROWN_B>;
		os << termcolor::white;
	} else if (colour_type_ == "Light Blue") {
		os << termcolor::on_color<LIGHT_BLUE_R, LIGHT_BLUE_G, LIGHT_BLUE_B>;
		os << termcolor::color<255, 255, 255>;
	} else if (colour_type_ == "Pink") {
		os << termcolor::on_color<PINK_R, PINK_G, PINK_B>;
		os << termcolor::white;
	} else if (colour_type_ == "Orange") {
		os << termcolor::on_color<ORANGE_R, ORANGE_G, ORANGE_B>;
		os << termcolor::white;
	} else if (colour_type_ == "Red") {
		os << termcolor::on_color<RED_R, RED_G, RED_B>;
		os << termcolor::white;
	} else if (colour_type_ == "Yellow") {
		os << termcolor::on_color<YELLOW_R, YELLOW_G, YELLOW_B>;
		os << termcolor::color<255, 255, 255>;
	} else if (colour_type_ == "Green") {
		os << termcolor::on_color<GREEN_R, GREEN_G, GREEN_B>;
		os << termcolor::white;
	} else if (colour_type_ == "Blue") {
		os << termcolor::on_color<BLUE_R, BLUE_G, BLUE_B>;
		os << termcolor::white;
	}
	std::string padding_left = " ";
	int padding_left_size = (k_max_tile_name_length - name_.length()) / 2;
	for (int i = 0; i < padding_left_size; i++) {
		padding_left += " ";
	}
	std::string padding_right = " ";
	int padding_right_size = k_max_tile_name_length - name_.length() - padding_left_size;
	for (int i = 0; i < padding_right_size; i++) {
		padding_right += " ";
	}
	os << padding_left << name_ << padding_right << termcolor::reset;

	std::string padding = "";
	os << termcolor::italic << " ";
	if (owner_ == "Bank") {
		os << "(Unowned)";
		padding = "   ";
	} else {
		os << "(" << owner_ << ")";
		padding = "";
		int padding_size = k_max_player_name_length - owner_.length();
		for (int i = 0; i < padding_size; i++) {
			padding += " ";
		}
	}

	os << termcolor::reset << padding << " ";

	for (int i = 0; i < 5; i++) {
		os << "[";
		if (tile_level_ - 2 >= i) {
			os << "#";
		} else {
			os << " ";
		}
		os << "] ";
	}

	padding = "";
	for (int i = 0; i < k_padding_to_cost_rent; ++i) {
		padding += " ";
	}
	os << padding;

	os << termcolor::underline;

	if (owner_ != "Bank") {
		os << "Rent: " << rent_.at(tile_level_);
	} else {
		os << "Buy for: $" << tile_cost_;
	}

	os << termcolor::reset << std::endl;
}