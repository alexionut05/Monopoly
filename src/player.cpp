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
	is_in_jail_ = false;
} 

Player::~Player() {};

// Getters
bool Player::IsActive() const
{
	return is_active_;
}

bool Player::IsInJail() const
{
	return is_in_jail_;
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

void Player::SetInJail(bool is_in_jail)
{
	is_in_jail_ = is_in_jail;
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

// Methods
void Player::AddBalance(int amount)
{
	balance_ += amount;
}

void Player::AddJailTurns(int amount)
{
	jail_turns_ += amount;
}

void Player::AddGetOutOfJailCard(int amount)
{
	get_out_of_jail_cards_count_ += amount;
}

void Player::AddDoubleCount(int amount)
{
	double_count_ += amount;
}

bool Player::IsDoomedInJail(const int bail) const
{
	if (jail_turns_ > 3 && balance_ < bail && get_out_of_jail_cards_count_ == 0) {
		return true;
	}
	return false;
}