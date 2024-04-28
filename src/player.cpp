#include "player.hpp"

// Constructors and Destructor
Player::Player() {};

Player::Player(const std::string& name)
{
	name_ = name;
	balance_ = 1500;
	position_ = 0;
	jail_turns_ = 0;
	get_out_of_jail_cards_count_ = 0;
	double_count_ = 0;
	is_active_ = true;
} 

Player::~Player() {};

// Getters
bool Player::IsActive() const
{
	return is_active_;
}

std::string Player::GetName() const
{
	return name_;
}

int Player::GetBalance() const
{
	return balance_;
}

int Player::GetPosition() const
{
	return position_;
}

int Player::GetJailTurns() const
{
	return jail_turns_;
}

int Player::GetGetOutOfJailCardsCount() const
{
	return get_out_of_jail_cards_count_;
}

int Player::GetDoubleCount() const
{
	return double_count_;
}

// Setters
void Player::SetActive(bool is_active)
{
	is_active_ = is_active;
}

void Player::SetName(const std::string& name)
{
	name_ = name;
}

void Player::SetBalance(int balance)
{
	balance_ = balance;
}

void Player::SetPosition(int position, bool is_jail)
{
	position_ = position;
	if (is_jail == true) {
		jail_turns_ = 3;
	}
}

void Player::SetJailTurns(int jail_turns)
{
	jail_turns_ = jail_turns;
}

void Player::SetGetOutOfJailCardsCount(int get_out_of_jail_cards_count)
{
	get_out_of_jail_cards_count_ = get_out_of_jail_cards_count;
}

void Player::SetDoubleCount(int double_count)
{
	double_count_ = double_count;
}