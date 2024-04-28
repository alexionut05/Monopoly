#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
public:
	// Constructor and destructor
	Player(const std::string& name, const int balance);
	~Player();

	// Getters
	bool IsInJail() const;
	std::string GetName() const;
	int GetBalance() const;
	int GetPosition() const;
	int GetJailTurns() const;
	int GetGetOutOfJailCardsCount() const;
	int GetDoubleCount() const;

	// Setters (needed for easy moving of players)
	void SetPosition(const int position);

	// Methods
	void AddBalance(int amount);
	void AddJailTurns(int amount);
	void AddGetOutOfJailCard(int amount);
	void AddDoubleCount(int amount);
	bool IsDoomedInJail(const int bail) const;
	
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