#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "deck.hpp"
#include "dice.hpp"
#include "player.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>
#include <termcolor/termcolor.hpp>

class Game {
public:
	// Constructor and Destructor
	Game(const std::string &language, const int dice_min, const int dice_max, const int player_start_balance, 
		const size_t min_players, const size_t max_players, const size_t min_name_length, const size_t max_name_length, 
		const int chance_deck_size, const int community_deck_size, const int bail_value, const std::string &bank_name);
	~Game();

	// Game methods
	void InitGame();
	void RunGame();
	void EndGame(const int winner_index);
	void PlayTurn(const int player_index);

	// Locales methods
	void InitLocales();

	// Player methods
	void InitPlayers();
	bool IsPlayerNameValid(const std::string &name) const;
	void AddPlayer(const Player &player);
	void RemovePlayer(const int player_index);

	// Board methods
	void MovePlayerAt(const int player_index, const int position);
	void MovePlayerBy(const int player_index, const int steps);

	// Print methods
	void PrintBlank();
	void PrintTurnStartJail(const int player_index);
	void PrintJailBroke();
	void PrintOptionInfoTile();
	void PrintOptionBuyTile();
	void PrintOptionSellTile();
	void PrintOptionBuyHouse();
	void PrintOptionSellHouse();
	void PrintOptionUseGetOutOfJailCard(const int player_index);
	void PrintOptionTryDouble();
	void PrintOptionPayFine();

	// Clear screen
	void ClearScreen();

private:
	Board board_;
	Deck chance_deck_;
	Deck community_deck_;
	Dice dice_;
	std::vector<Player> players_;

	const std::string language_;
	const int player_start_balance_;
	const size_t min_players_;
	const size_t max_players_;
	const size_t min_name_length_;
	const size_t max_name_length_;

	// Locales
	nlohmann::json game_locales_;
	nlohmann::json player_locales_;
};

#endif // "GAME_HPP"