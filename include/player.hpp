#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

class Player {
public:
	Player(const std::string& name, const int balance);

	bool IsInJail() const;
	std::string GetName() const;
	int GetBalance() const;
	int GetPosition() const;
	int GetJailTurns() const;
	int GetGetOutOfJailCardsCount() const;
	int GetDoubleCount() const;

	void SetPosition(const int position);
	void GoToJail();
	void GetOutOfJail();

	void AddBalance(const int amount);
	void AddJailTurns(const int amount = 1);
	void AddGetOutOfJailCard(const int amount = 1);
	void AddDoubleCount(const int amount);
	bool IsDoomedInJail(const int bail) const;

	friend std::ostream& operator<<(std::ostream& out, const Player& player);
	
private:
	bool is_in_jail_;
	std::string name_;
	int balance_;
	int position_;
	int jail_turns_;
	int get_out_of_jail_cards_count_;
	int double_count_;
};

#endif // PLAYER_HPP