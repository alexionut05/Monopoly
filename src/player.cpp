#include "player.hpp"

// Constructors and Destructor
Player::Player(const std::string& name, const int balance)
	: name_(name), balance_(balance), position_(0), jail_turns_(0), get_out_of_jail_cards_count_(0), double_count_(0), is_in_jail_(false) {}

Player::~Player() {};

// Getters
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
void Player::SetPosition(const int position)
{
	position_ = position;
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