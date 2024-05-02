#include "player.hpp"

Player::Player(const std::string& name, const int balance)
	: is_in_jail_(false), name_(name), balance_(balance), position_(0), jail_turns_(0), get_out_of_jail_cards_count_(0), double_count_(0) {}

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

void Player::SetPosition(const int position)
{
	position_ = position;
}

void Player::GoToJail()
{
	is_in_jail_ = true;
	position_ = 10;
	jail_turns_ = 0;
	double_count_ = 0;
}

void Player::GetOutOfJail()
{
	is_in_jail_ = false;
	jail_turns_ = 0;
}

void Player::AddBalance(const int amount)
{
	balance_ += amount;
}

void Player::AddJailTurns(const int amount)
{
	jail_turns_ += amount;
}

void Player::AddGetOutOfJailCard(const int amount)
{
	get_out_of_jail_cards_count_ += amount;
}

void Player::AddDoubleCount(const int amount)
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

// pt tema 1
std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << "Player: " << player.name_ << std::endl;
	out << "Balance: " << player.balance_ << std::endl;
	out << "Position: " << player.position_ << std::endl;
	out << "Jail turns: " << player.jail_turns_ << std::endl;
	out << "Get out of jail cards: " << player.get_out_of_jail_cards_count_ << std::endl;
	out << "Double count: " << player.double_count_ << std::endl;
	return out;
}