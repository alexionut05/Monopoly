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
	// Constructor
	Game(const std::string &language, const int dice_min, const int dice_max, const int player_start_balance, 
		const size_t min_players, const size_t max_players, const size_t min_name_length, const size_t max_name_length, 
		const int chance_deck_size, const int community_deck_size, const int bail_value, const std::string &bank_name);

	// Game methods
	void InitGame();
	void RunGame();
	void EndGame(const Player &winner);
	void PlayTurn(Player &player);
	void PlayTurnInJail(Player &player);

	// Locales methods
	void InitLocales();

	// Player methods
	void InitPlayers();
	bool IsPlayerNameValid(const std::string &name) const;
	void AddPlayer(const Player &player);
	void RemovePlayer(const Player &player);
	bool PromptPlayerReady(const Player &player);
	int FindPlayerByName(const std::string &name) const;

	// Board methods
	void MovePlayerAt(Player &player, const int position, const bool init = false);
	void MovePlayerBy(Player &player, const int steps);
	void MovePlayerToJail(Player &player);
	bool IsPlayerEnabledTile(Tile *tile) const;
	bool CanAffordTransaction(const Player &player, const int amount) const;
	bool IsPlayerOwnedTile(Tile *tile) const;
	int GetHousesOnTile(Tile *tile) const;
	int GetHouseCost(Tile *tile) const;
	int HandlePlayerArrivalAtTile(Player &player, Tile *tile, int multiplier = 1);
	void PayRent(Player &payer, Player &owner, const int rent);
	int HandleDrawCard(Player &player, const std::string &card_type, int &multiplier);

	// Print methods
	void PrintBlank();
	void PrintTurnStart(const Player &player);
	void PrintTurnStartJail(const Player &player);
	void PrintOptionIllegal();
	void PrintOptionRollDice();
	void PrintOptionQuitGame();
	void PrintOptionPrintBoard();
	void PrintOptionInfo();
	void PrintOptionBuyTile(const Player &player);
	void PrintOptionSellTile();
	void PrintOptionBuyHouse();
	void PrintOptionSellHouse();
	void PrintOptionEndTurn();
	void PrintOptionJailRoll();
	void PrintOptionJailPay();
	void PrintOptionJailUseCard(const Player &player);
	void PrintPlayerDoomedInJail(const Player &player);


	// Action methods
	std::pair<int, int> ActionRollDice();
	bool ActionQuitGame(const Player &player);
	void ActionInfo();
	void ActionBuyTile(Player &player);
	void ActionSellTile(Player &player);
	void ActionBuyHouse(Player &player);
	void ActionSellHouse(Player &player);
	bool ActionEndTurn(const Player &player);

	// Clear screen
	void ClearScreen();

	// Operator Overloads	
	friend std::ostream &operator<<(std::ostream &os, const Game &game);

	int MaxInt(const int a, const int b) const;

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