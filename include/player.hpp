#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
public:
	// Constructors and destructor
	Player();
	Player(const std::string& name);
	~Player();

	// Getters
	bool IsActive() const;
	std::string GetName() const;
	int GetBalance() const;
	int GetPosition() const;
	int GetJailTurns() const;
	int GetGetOutOfJailCardsCount() const;
	int GetDoubleCount() const;

	// Setters
	void SetActive(bool is_active);
	void SetName(const std::string& name);
	void SetBalance(int balance);
	void SetPosition(int position, bool is_jail = false);
	void SetJailTurns(int jail_turns);
	void SetGetOutOfJailCardsCount(int get_out_of_jail_cards_count);
	void SetDoubleCount(int double_count);

	// Methods
	void AddBalance(int amount);
	void AddPosition(int amount);
	void AddGetOutOfJailCardsCount(int amount);
	void AddDoubleCount(int amount);

private:
	bool is_active_;
	std::string name_;
	int balance_;
	int position_;
	int jail_turns_;
	int get_out_of_jail_cards_count_;
	int double_count_;
};

#endif // PLAYER_HPP