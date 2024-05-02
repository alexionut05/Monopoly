#include "game.hpp"

// Constructor
Game::Game(const std::string &language, const int dice_min, const int dice_max, const int player_start_balance, 
	const size_t min_players, const size_t max_players, const size_t min_name_length, const size_t max_name_length, 
	const int chance_deck_size, const int community_deck_size, const int bail_value, const std::string &bank_name)
	: board_(bail_value, bank_name, "../locales/" + language + "/tiles.json"), chance_deck_(language, "chance", chance_deck_size),
	community_deck_(language, "community_chest", community_deck_size), dice_(dice_min, dice_max), players_({}),
	language_(language), player_start_balance_(player_start_balance),
	min_players_(min_players), max_players_(max_players), min_name_length_(min_name_length), max_name_length_(max_name_length) {}

// Game methods
void Game::InitGame()
{
	ClearScreen();

	// Init board
	board_.InitBoard();
	std::cout << board_;

	// Load locales
	InitLocales();

	// Welcome message
	std::string message = game_locales_["welcome"].get<std::string>();
	std::cout << message << std::endl;

	// Init decks
	chance_deck_.InitDeck();
	community_deck_.InitDeck();

	// Init players
	InitPlayers();

	// Run game
	RunGame();
}

void Game::RunGame()
{
	// Game loop
	int winner_index = -1;
	while (winner_index == -1) {
		for (size_t i = 0; i < players_.size(); ++i) {
			bool player_ready = false;
			ClearScreen();
			do {
				player_ready = PromptPlayerReady(players_[i]);
			} while (player_ready == false);

			PlayTurn(players_[i]);
			if (players_[i].GetBalance() < 0) {
				RemovePlayer(players_[i]);
				--i;
			}
		}
		if (players_.size() == 1) {
			winner_index = 0;
		}
	}

	// End game
	EndGame(players_[winner_index]);
}

void Game::EndGame(const Player &winner)
{
	std::string message = game_locales_["winner"].get<std::string>();
	std::string placeholder = "{{winner}}";
	message.replace(message.find(placeholder), placeholder.length(), winner.GetName());
	std::cout << message << std::endl;

	message = game_locales_["thanks"].get<std::string>();
	placeholder = "{{nl}}";
	message.replace(message.find(placeholder), placeholder.length(), "\n");
	std::cout << message << std::endl;
}

void Game::PlayTurn(Player &player)
{

	ClearScreen();
	std::cout << board_ << std::endl << std::endl;

	// Player is in jail
	if (player.IsInJail() == true) {
		PlayTurnInJail(player);
		return;
	}

	// Player is not in jail
	// Before roll
	char option = ' ';
	std::pair<int, int> dice_values;
	do {
		PrintBlank();
		PrintTurnStart(player);
		PrintOptionPrintBoard();
		PrintOptionInfo();
		PrintOptionSellTile();
		PrintOptionBuyHouse();
		PrintOptionSellHouse();
		PrintOptionRollDice();
		PrintOptionQuitGame();
		PrintBlank();
		std::cout << std::endl;
		std::cin >> option;
		option = std::tolower(option);
		PrintBlank();

		bool quit_confirm;

		switch (option) {
		case 't':
			std::cout << board_ << std::endl << std::endl;
			break;
		case 'i':
			ActionInfo();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 's':
			ActionSellTile(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'h':
			ActionBuyHouse(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'l':
			ActionSellHouse(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'r':
			ClearScreen();
			PrintBlank();
			dice_values = ActionRollDice();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'q':
			quit_confirm = ActionQuitGame(player);
			PrintBlank();
			std::cout << std::endl << std::endl;

			if (quit_confirm == true) {
				return;
			}
			break;
		default:
			PrintOptionIllegal();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		}
	} while (option != 'r');

	// After roll
	bool can_roll_again = false;
	ClearScreen();
	MovePlayerBy(player, dice_values.first + dice_values.second);
	std::cout << board_ << std::endl << std::endl;

	if (dice_values.first == dice_values.second) {
		player.AddDoubleCount(1);
		if (player.GetDoubleCount() == 3) {
			PrintBlank();
			std::cout << game_locales_["action_roll_dice_double_jail"].get<std::string>() << std::endl;
			PrintBlank();
			std::cout << std::endl << std::endl;
			MovePlayerToJail(player);
			return;
		} else {
			can_roll_again = true;
			PrintBlank();
			std::cout << game_locales_["action_roll_dice_double_safe"].get<std::string>() << std::endl;
			PrintBlank();
			std::cout << std::endl << std::endl;
		}
	}

	// Move player
	Tile *tile = board_.GetTileAt(player.GetPosition()).get();
	std::string message = game_locales_["action_move"].get<std::string>();
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	PrintBlank();
	std::cout << message << std::endl;
	PrintBlank();
	std::cout << std::endl << std::endl;

	// Tile action
	// 0 = default
	// 1 = jail
	// 2 = can buy
	int tile_result = HandlePlayerArrivalAtTile(player, tile);

	if (tile_result != 1) {
		do {
			PrintBlank();
			PrintTurnStart(player);
			PrintOptionPrintBoard();
			PrintOptionInfo();
			if (tile_result == 2) {
				PrintOptionBuyTile(player);
			}
			PrintOptionSellTile();
			PrintOptionBuyHouse();
			PrintOptionSellHouse();
			PrintOptionEndTurn();
			PrintOptionQuitGame();
			PrintBlank();
			std::cout << std::endl;
			std::cin >> option;
			option = std::tolower(option);
			PrintBlank();

			bool quit_confirm;

			switch (option) {
			case 't':
				std::cout << board_ << std::endl << std::endl;
				break;
			case 'i':
				ActionInfo();
				break;
			case 'b':
				if (tile_result == 2) {
					ActionBuyTile(player);
					PrintBlank();
					std::cout << std::endl << std::endl;
				} else {
					PrintOptionIllegal();
					PrintBlank();
					std::cout << std::endl << std::endl;
				}
				break;
			case 's':
				ActionSellTile(player);
				PrintBlank();
				std::cout << std::endl << std::endl;
				break;
			case 'h':
				ActionBuyHouse(player);
				PrintBlank();
				std::cout << std::endl << std::endl;
				break;
			case 'l':
				ActionSellHouse(player);
				PrintBlank();
				std::cout << std::endl << std::endl;
				break;
			case 'e':
				quit_confirm = ActionEndTurn(player);
				PrintBlank();
				std::cout << std::endl << std::endl;
				break;
			case 'q':
				quit_confirm = ActionQuitGame(player);
				PrintBlank();
				std::cout << std::endl << std::endl;

				if (quit_confirm == true) {
					return;
				}
				break;
			default:
				PrintOptionIllegal();
				PrintBlank();
				std::cout << std::endl << std::endl;
				break;
			}
		} while (option != 'e');
	}

	if (can_roll_again == true) {
		PlayTurn(player);
	}
}

void Game::PlayTurnInJail(Player &player)
{
	ClearScreen();
	std::cout << board_ << std::endl;

	bool can_try_roll = player.GetJailTurns() < 4;
	bool can_use_card = player.GetGetOutOfJailCardsCount() > 0;
	char option = ' ';

	bool escaped = false;

	do {
		PrintBlank();
		PrintTurnStartJail(player);
		PrintOptionPrintBoard();
		PrintOptionInfo();
		if (player.IsDoomedInJail(board_.GetBailValue()) == true) {
			PrintPlayerDoomedInJail(player);
		}
		PrintOptionSellTile();
		PrintOptionBuyHouse();
		PrintOptionSellHouse();
		if (can_try_roll == true) {
			PrintOptionJailRoll();
		}
		if (can_use_card == true) {
			PrintOptionJailUseCard(player);
		}
		PrintOptionJailPay();
		PrintOptionQuitGame();
		PrintBlank();
		std::cout << std::endl;
		std::cin >> option;
		option = std::tolower(option);
		PrintBlank();

		bool quit_confirm;

		std::string message;
		std::string placeholder;

		switch (option) {
		case 't':
			std::cout << board_ << std::endl << std::endl;
			break;
		case 'i':
			ActionInfo();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 's':
			ActionSellTile(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'b':
			ActionBuyHouse(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'l':
			ActionSellHouse(player);
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'r':
			if (can_try_roll == true) {
				ClearScreen();
				PrintBlank();
				std::pair<int, int> dice_values = ActionRollDice();
				PrintBlank();
				std::cout << std::endl << std::endl;

				if (dice_values.first == dice_values.second) {
					message = game_locales_["action_roll_dice_double_escape"].get<std::string>();
					std::cout << message << std::endl;
					player.GetOutOfJail();
					escaped = true;
					MovePlayerBy(player, dice_values.first + dice_values.second);
					message = game_locales_["action_move"].get<std::string>();
					placeholder = "{{tile_name}}";
					message.replace(message.find(placeholder), placeholder.length(), board_.GetTileAt(player.GetPosition())->GetName());
					std::cout << message << std::endl;
					PrintBlank();
					std::cout << std::endl << std::endl;
				} else {
					message = game_locales_["action_roll_dice_double_fail"].get<std::string>();
					std::cout << message << std::endl;
					PrintBlank();
					std::cout << std::endl << std::endl;
				}
			} else {
				PrintOptionIllegal();
				PrintBlank();
				std::cout << std::endl << std::endl;
			}
			break;
		case 'j':
			if (can_use_card == true) {
				player.AddGetOutOfJailCard(-1);
				player.GetOutOfJail();
				escaped = true;
				message = game_locales_["action_use_card"].get<std::string>();
				std::cout << message << std::endl;
				PrintBlank();
				std::cout << std::endl << std::endl;
			} else {
				PrintOptionIllegal();
				PrintBlank();
				std::cout << std::endl << std::endl;
			}
			break;
		case 'p':
			player.AddBalance(-board_.GetBailValue());
			player.GetOutOfJail();
			escaped = true;
			message = game_locales_["action_pay_fine"].get<std::string>();
			placeholder = "{{fine}}";
			message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBailValue()));
			std::cout << message << std::endl;
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'q':
			quit_confirm = ActionQuitGame(player);
			PrintBlank();
			std::cout << std::endl << std::endl;

			if (quit_confirm == true) {
				return;
			}
			break;
		default:
			PrintOptionIllegal();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		}
	} while (option != 'q' && escaped == false);

	if (escaped == false) {
		player.AddJailTurns();
	}
}

// Locales methods
void Game::InitLocales()
{
	// Load game locales
	std::ifstream file("../locales/" + language_ + "/game.json");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open game locales file." << std::endl;
		exit(1);
	}
	game_locales_ = nlohmann::json::parse(file);
	file.close();

	// Load player locales
	file.open("../locales/" + language_ + "/player.json");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open player locales file." << std::endl;
		exit(1);
	}
	player_locales_ = nlohmann::json::parse(file);
	file.close();
}

// Player methods
void Game::InitPlayers()
{
	// Get number of players
	size_t num_players;
	std::string message = player_locales_["init_count"].get<std::string>();
	std::string placeholder = "{{min}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(min_players_));
	placeholder = "{{max}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(max_players_));
	
	do {
		std::cout << message;
		std::cin >> num_players;
		if (num_players < min_players_ || num_players > max_players_) {
			std::cout << player_locales_["invalid_count"].get<std::string>() << std::endl << std::endl;
		}
	} while (num_players < min_players_ || num_players > max_players_);

	// Get player names
	for (size_t i = 0; i < num_players; ++i) {
		message = player_locales_["init_name"].get<std::string>();
		placeholder = "{{count}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(i + 1));
		std::string name;

		do {
			std::cout << message;
			std::cin >> name;
		} while (IsPlayerNameValid(name) == false);

		AddPlayer(Player(name, player_start_balance_));
		MovePlayerAt(players_[i], 0, true);
	}
}

bool Game::IsPlayerNameValid(const std::string &name) const
{
	std::string name_copy = name;
	std::transform(name_copy.begin(), name_copy.end(), name_copy.begin(), ::toupper);
	if (name.length() < min_name_length_) {
		std::string message = player_locales_["short_name"].get<std::string>();
		std::string placeholder = "{{min}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(min_name_length_));
		std::cout << message << std::endl << std::endl;
		return false;
	}
	if (name.length() > max_name_length_) {
		std::string message = player_locales_["long_name"].get<std::string>();
		std::string placeholder = "{{max}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(max_name_length_));
		std::cout << message << std::endl << std::endl;
		return false;
	}
	std::string bank_name = board_.GetBankName();
	std::transform(bank_name.begin(), bank_name.end(), bank_name.begin(), ::toupper);
	if (name_copy == bank_name) {
		std::cout << player_locales_["bank_name"].get<std::string>() << std::endl << std::endl;
		return false;
	}
	for (const auto &player : players_) {
		std::string player_name = player.GetName();
		std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::toupper);
		if (name_copy == player_name) {
			std::cout << player_locales_["duplicate_name"].get<std::string>() << std::endl << std::endl;
			return false;
		}
	}
	return true;
}

void Game::AddPlayer(const Player &player)
{
	players_.push_back(player);
}

void Game::RemovePlayer(Player &player)
{
	std::string message = player_locales_["remove_player"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), player.GetName());
	std::cout << message << std::endl;

	std::string removed_player_name = player.GetName();

	for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
		if (board_.GetTileAt(i)->GetOwner() == removed_player_name) {
			board_.InitTile(i);
		}
	}

	for (size_t i = 0; i < players_.size(); ++i) {
		if (players_[i].GetName() == removed_player_name) {
			players_.erase(players_.begin() + i);
			break;
		}
	}
}

bool Game::PromptPlayerReady(const Player &player)
{
	std::string message = player_locales_["ready"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), player.GetName());
	std::cout << message;

	char ready;
	std::cin >> ready;
	ready = std::tolower(ready);

	if (ready == 'y') {
		return true;
	}
	return false;
}

int Game::FindPlayerByName(const std::string &name) const
{
	for (size_t i = 0; i < players_.size(); ++i) {
		if (players_[i].GetName() == name) {
			return i;
		}
	}
	return -1;
}

// Board methods
void Game::MovePlayerAt(Player &player, const int position, const bool init)
{
	if (position <= player.GetPosition() && init == false) {
		int pass_go = dynamic_cast<Go*>(board_.GetTileAt(0).get())->GetPassGoAmount();
		player.AddBalance(pass_go);
	}
	board_.GetTileAt(player.GetPosition())->RemovePlayerHere(player.GetName());
	board_.GetTileAt(position)->AddPlayerHere(player.GetName());
	player.SetPosition(position);
}

void Game::MovePlayerBy(Player &player, const int steps)
{
	int new_position = player.GetPosition() + steps;
	if (new_position >= static_cast<int>(board_.GetBoardSize())) {
		new_position -= board_.GetBoardSize();
		int pass_go = dynamic_cast<Go*>(board_.GetTileAt(0).get())->GetPassGoAmount();
		player.AddBalance(pass_go);
	
	}
	MovePlayerAt(player, new_position);
}

void Game::MovePlayerToJail(Player &player)
{
	player.GoToJail();
	for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
		if (dynamic_cast<Jail*>(board_.GetTileAt(i).get()) != nullptr) {
			Jail *jail = dynamic_cast<Jail*>(board_.GetTileAt(i).get());
			jail->AddPlayerJailed(player.GetName());
			break;
		}
	}
}


bool Game::IsPlayerEnabledTile(Tile *tile) const
{
	//dynamic casts to check
	if (dynamic_cast<Property*>(tile) != nullptr) {
		return true;
	}
	if (dynamic_cast<Railroad*>(tile) != nullptr) {
		return true;
	}
	if (dynamic_cast<Utility*>(tile) != nullptr) {
		return true;
	}
	return false;
}

bool Game::CanAffordTransaction(const Player &player, const int amount) const
{
	if (player.GetBalance() >= amount) {
		return true;
	}
	return false;
}

bool Game::IsPlayerOwnedTile(Tile *tile) const
{
	if (tile->GetOwner() != board_.GetBankName()) {
		return true;
	}
	return false;
}

int Game::GetHousesOnTile(Tile *tile) const
{
	if (dynamic_cast<Property*>(tile) != nullptr) {
		Property *property = dynamic_cast<Property*>(tile);
		if (property->GetTileLevel() >= 2) {
			return property->GetTileLevel() - 1;
		}
	}
	return 0;
}

int Game::GetHouseCost(Tile *tile) const
{
	if (dynamic_cast<Property*>(tile) != nullptr) {
		Property *property = dynamic_cast<Property*>(tile);
		int cost = property->GetBuildingCost();
		return cost;
	}
	return -1;
}

// Function to handle the player arrival at a tile
// Return values:
//     0 = nothing happens
//     1 = jail
//     2 = can buy
int Game::HandlePlayerArrivalAtTile(Player &player, Tile *tile, int multiplier)
{
	int goes_to_jail = 0;
	int can_buy = 0;
	bool function_repeat = false;
	if (dynamic_cast<Property*>(tile) != nullptr) {
		Property *property = dynamic_cast<Property*>(tile);
		if (property->GetOwner() == board_.GetBankName()) {
			can_buy = 1;
		} else if (property->GetOwner() != player.GetName()) {
			PrintBlank();
			int rent = property->GetRent()[property->GetTileLevel()];
			PayRent(player, players_[FindPlayerByName(property->GetOwner())], rent);
			PrintBlank();
			std::cout << std::endl << std::endl;
		}
	} else if (dynamic_cast<Railroad*>(tile) != nullptr) {
		Railroad *railroad = dynamic_cast<Railroad*>(tile);
		if (railroad->GetOwner() == board_.GetBankName()) {
			can_buy = 1;
		} else if (railroad->GetOwner() != player.GetName()) {
			PrintBlank();
			int rent = railroad->GetRent()[railroad->GetTileLevel()] * multiplier;
			PayRent(player, players_[FindPlayerByName(railroad->GetOwner())], rent);
			PrintBlank();
			std::cout << std::endl << std::endl;
		}
	} else if (dynamic_cast<Utility*>(tile) != nullptr) {
		Utility *utility = dynamic_cast<Utility*>(tile);
		if (utility->GetOwner() == board_.GetBankName()) {
			can_buy = 1;
		} else if (utility->GetOwner() != player.GetName()) {
			PrintBlank();
			std::pair <int, int> dice_values = ActionRollDice();
			int dice_total = dice_values.first + dice_values.second;
			int rent = std::max(utility->GetDiceMultiplier()[utility->GetTileLevel()], multiplier) * dice_total;
			PayRent(player, players_[FindPlayerByName(utility->GetOwner())], rent);
			PrintBlank();
			std::cout << std::endl << std::endl;
		
		}
	} else if (dynamic_cast<CardTile*>(tile) != nullptr) {
		CardTile *card_tile = dynamic_cast<CardTile*>(tile);
		std::string card_type = card_tile->GetName();
		// This will handle the outcome of the card
		// 0 = nothing happens
		// 1 = jail
		// 2 = move card (will repeat this function)
		PrintBlank();
		int result = HandleDrawCard(player, card_type, multiplier);
		PrintBlank();
		std::cout << std::endl << std::endl;
		if (result == 1) {
			goes_to_jail = 1;
		} else if (result == 2) {
			function_repeat = true;
		}
	} else if (dynamic_cast<GoToJail*>(tile) != nullptr) {
		MovePlayerToJail(player);
		goes_to_jail = 1;
	} else if (dynamic_cast<Tax*>(tile) != nullptr) {
		Tax *tax = dynamic_cast<Tax*>(tile);
		player.AddBalance(-tax->GetTaxAmount());
	}

	if (goes_to_jail == 1) {
		return 1;
	}
	if (function_repeat == true) {
		HandlePlayerArrivalAtTile(player, board_.GetTileAt(player.GetPosition()).get(), multiplier);
	}

	if (can_buy == 1) {
		return 2;
	}

	return 0;
}

void Game::PayRent(Player &payer, Player &owner, const int rent)
{
	std::string message = game_locales_["action_pay_rent"].get<std::string>();
	std::string placeholder = "{{rent}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(rent));
	placeholder = "{{owner}}";
	message.replace(message.find(placeholder), placeholder.length(), owner.GetName());
	std::cout << message << std::endl;

	payer.AddBalance(-rent);
	owner.AddBalance(rent);
}

// Fuction to handle drawing a card by the player
// Return values:
//     0 = nothing happens
//     1 = jail
//     2 = move card (will repeat the HandlePlayerArrivalAtTile function)
int Game::HandleDrawCard(Player &player, const std::string deck_type, int &multiplier)
{
	std::string message = game_locales_["action_draw_card"].get<std::string>();
	std::string placeholder = "{{card_type}}";
	message.replace(message.find(placeholder), placeholder.length(), deck_type);
	std::cout << message << std::endl;
	
	Card card;
	if (deck_type == "Chance") {
		card = chance_deck_.DrawCard();
	} else if (deck_type == "Community Chest") {
		card = community_deck_.DrawCard();
	}

	std::cout << "# \"" << card.GetDescription() << "\"" << std::endl;

	if (card.GetType() == "Advance") {
		int position = card.GetValue().first;
		MovePlayerAt(player, position);
		return 2;
	}
	if (card.GetType() == "Advance Nearest") {
		int destination_type = card.GetValue().first;
		multiplier = card.GetValue().second;
		int min_distance = board_.GetBoardSize();
		int destination_idx = -1;
		if (destination_type == 8584) {
			// 8584 == UT (ascii)
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Utility*>(board_.GetTileAt(i).get()) != nullptr) {
					int distance = i - player.GetPosition();
					if (distance < 0) {
						distance += board_.GetBoardSize();
					}
					if (distance < min_distance) {
						min_distance = distance;
						destination_idx = i;
					}
				}
			}
		} else if (destination_type == 8282) {
			// 8282 == RR (ascii)
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Railroad*>(board_.GetTileAt(i).get()) != nullptr) {
					int distance = i - player.GetPosition();
					if (distance < 0) {
						distance += board_.GetBoardSize();
					}
					if (distance < min_distance) {
						min_distance = distance;
						destination_idx = i;
					}
				}
			}
		}
		if (destination_idx != -1) {
			MovePlayerAt(player, destination_idx);
			HandlePlayerArrivalAtTile(player, board_.GetTileAt(destination_idx).get(), multiplier);
			return 2;
		}
	}
	if (card.GetType() == "Balance") {
		int amount = card.GetValue().first;
		player.AddBalance(amount);
		return 0;
	}
	if (card.GetType() == "Balance All") {
		int amount = card.GetValue().first;
		for (auto &other_player : players_) {
			if (other_player.GetName() != player.GetName()) {
				player.AddBalance(amount);
				other_player.AddBalance(-amount);
			}
		}
		return 0;
	}
	if (card.GetType() == "Get Out Of Jail") {
		player.AddGetOutOfJailCard();
		return 0;
	}
	if (card.GetType() == "Go To Jail") {
		MovePlayerToJail(player);
		return 1;
	}
	if (card.GetType() == "Move") {
		int amount = card.GetValue().first;
		MovePlayerBy(player, amount);
		return 2;
	}
	if (card.GetType() == "Repairs") {
		int house_cost = card.GetValue().first;
		int hotel_cost = card.GetValue().second;
		int total_cost = 0;
		
		for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
			Tile *tile = board_.GetTileAt(i).get();
			if (dynamic_cast<Property*>(tile) != nullptr) {
				Property *property = dynamic_cast<Property*>(tile);
				if (property->GetOwner() == player.GetName()) {
					int house_count = property->GetTileLevel() - 1;
					if (house_count == 5) {
						total_cost += hotel_cost;
					} else {
						total_cost += house_count * house_cost;
					}
				}
			}
		}

		player.AddBalance(-total_cost);
		return 0;
	}
	else {
		return 0;
	}
}

// Print methods
void Game::PrintBlank()
{
	std::cout << game_locales_["blank"].get<std::string>() << std::endl;
}

void Game::PrintTurnStart(const Player &player)
{
	std::string message = game_locales_["turn_start"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), player.GetName());
	placeholder = "{{balance}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(player.GetBalance()));
	std::cout << message << std::endl;
}

void Game::PrintTurnStartJail(const Player &player)
{
	std::string message = game_locales_["turn_start_jail"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), player.GetName());
	std::cout << message << std::endl;
}

void Game::PrintOptionIllegal()
{
	std::string message = game_locales_["option_illegal"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionRollDice()
{
	std::string message = game_locales_["option_roll_dice"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionQuitGame()
{
	std::string message = game_locales_["option_quit_game"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionPrintBoard()
{
	std::string message = game_locales_["option_print_board"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionInfo()
{
	std::string message = game_locales_["option_info"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionBuyTile(const Player &player)
{
	std::string message = game_locales_["option_buy_tile"].get<std::string>();
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), board_.GetTileAt(player.GetPosition())->GetName());
	placeholder = "{{tile_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetTileAt(player.GetPosition())->GetTileCost()));
	std::cout << message << std::endl;
}

void Game::PrintOptionSellTile()
{
	std::string message = game_locales_["option_sell_tile"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionBuyHouse()
{
	std::string message = game_locales_["option_buy_house"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionSellHouse()
{
	std::string message = game_locales_["option_sell_house"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionEndTurn()
{
	std::string message = game_locales_["option_end_turn"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionJailRoll()
{
	std::string message = game_locales_["option_jail_try_double"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::PrintOptionJailUseCard(const Player &player)
{
	std::string message = game_locales_["option_jail_use_card"].get<std::string>();
	std::string placeholder = "{{cards}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(player.GetGetOutOfJailCardsCount()));
	std::cout << message << std::endl;
}

void Game::PrintOptionJailPay()
{
	std::string message = game_locales_["option_jail_pay_fine"].get<std::string>();
	std::string placeholder = "{{fine}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBailValue()));
	std::cout << message << std::endl;
}

void Game::PrintPlayerDoomedInJail(const Player &player)
{
	std::string message = game_locales_["turn_jail_broke"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), player.GetName());
	placeholder = "{{bail}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBailValue()));
	placeholder = "{{nl}}";
	message.replace(message.find(placeholder), placeholder.length(), "\n");
	std::cout << message << std::endl;
}

// Action methods
std::pair<int, int> Game::ActionRollDice()
{
	std::pair<int, int> dice_values = dice_.RollDice();
	std::string message = game_locales_["action_roll_dice"].get<std::string>();
	std::string placeholder = "{{dice1}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(dice_values.first));
	placeholder = "{{dice2}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(dice_values.second));
	placeholder = "{{total}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(dice_values.first + dice_values.second));
	std::cout << message << std::endl;

	return dice_values;
}

bool Game::ActionQuitGame(Player &player)
{
	std::string message = game_locales_["action_quit_game"].get<std::string>();
	std::cout << message;

	char quit;
	std::cin >> quit;
	quit = std::tolower(quit);

	ClearScreen();
	std::cout << board_;
	PrintBlank();

	if (quit == 'y') {
		message = game_locales_["action_quit_game_confirm"].get<std::string>();
		std::string placeholder = "{{nl}}";
		message.replace(message.find(placeholder), placeholder.length(), "\n");
		std::cout << message << std::endl;

		RemovePlayer(player);
		return true;
	}
	

	return false;
}

void Game::ActionInfo()
{
	std::string message = game_locales_["action_info"].get<std::string>();
	std::cout << message << std::endl;
}

void Game::ActionBuyTile(Player &player)
{
	Tile *tile = board_.GetTileAt(player.GetPosition()).get();
	
	if (IsPlayerEnabledTile(tile) == false) {
		std::cout << game_locales_["tile_illegal_type"].get<std::string>() << std::endl;
		return;
	}
	if (IsPlayerOwnedTile(tile) == true) {
		std::cout << game_locales_["tile_illegal_owned"].get<std::string>() << std::endl;
		return;
	}
	if (CanAffordTransaction(player, tile->GetTileCost()) == false) {
		std::cout << game_locales_["tile_illegal_balance"].get<std::string>() << std::endl;
		return;
	}

	std::string message = game_locales_["action_buy_tile_confirm"].get<std::string>();
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	placeholder = "{{tile_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));

	std::cout << message;
	char confirm;
	std::cin >> confirm;

	if (confirm == 'y') {
		player.AddBalance(-tile->GetTileCost());
		tile->SetOwner(player.GetName());
		message = game_locales_["action_buy_tile_success"].get<std::string>();
		placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
		placeholder = "{{tile_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));
		std::cout << message << std::endl;
		
		if (dynamic_cast<Property*>(tile) != nullptr) {
			Property *property = dynamic_cast<Property*>(tile);
			bool all_colour = true;
			std::vector<int> colour_group;
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Property*>(board_.GetTileAt(i).get()) != nullptr) {
					Property *other_property = dynamic_cast<Property*>(board_.GetTileAt(i).get());
					if (other_property->GetColourType() == property->GetColourType()) {
						colour_group.push_back(i);
						if (other_property->GetOwner() != player.GetName()) {
							all_colour = false;
						}
					}
				}
			}
			if (all_colour == true) {
				for (size_t i = 0; i < colour_group.size(); ++i) {
					Property *other_property = dynamic_cast<Property*>(board_.GetTileAt(colour_group[i]).get());
					other_property->SetTileLevel(std::max(1, other_property->GetTileLevel()));
				}
			}
		} else if (dynamic_cast<Railroad*>(tile) != nullptr) {
			int owned_railroads = 0;
			std::vector<int> railroad_group;
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Railroad*>(board_.GetTileAt(i).get()) != nullptr) {
					Railroad *railroad = dynamic_cast<Railroad*>(board_.GetTileAt(i).get());
					if (railroad->GetOwner() == player.GetName()) {
						++owned_railroads;
						railroad_group.push_back(i);
					}
				}
			}
			for (size_t i = 0; i < railroad_group.size(); ++i) {
				Railroad *railroad = dynamic_cast<Railroad*>(board_.GetTileAt(railroad_group[i]).get());
				railroad->SetTileLevel(std::max(owned_railroads - 1, 0));
			}
		} else if (dynamic_cast<Utility*>(tile) != nullptr) {
			int owned_utilities = 0;
			std::vector<int> utility_group;
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Utility*>(board_.GetTileAt(i).get()) != nullptr) {
					Utility *utility = dynamic_cast<Utility*>(board_.GetTileAt(i).get());
					if (utility->GetOwner() == player.GetName()) {
						++owned_utilities;
						utility_group.push_back(i);
					}
				}
			}
			for (size_t i = 0; i < utility_group.size(); ++i) {
				Utility *utility = dynamic_cast<Utility*>(board_.GetTileAt(utility_group[i]).get());
				utility->SetTileLevel(std::max(owned_utilities - 1, 0));
			}
		}
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_buy_tile_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
}

void Game::ActionSellTile(Player &player)
{
	std::string message = game_locales_["action_sell_tile"].get<std::string>();
	std::string placeholder = "{{board_size}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBoardSize()));
	std::cout << message;

	int option;
	std::cin >> option;
	if (option < 1 || option > static_cast<int>(board_.GetBoardSize())) {
		std::cout << game_locales_["tile_illegal"].get<std::string>() << std::endl;
		return;
	}

	Tile *tile = board_.GetTileAt(option - 1).get();

	if (tile->GetOwner() != player.GetName()) {
		std::cout << game_locales_["tile_illegal_not_owned"].get<std::string>() << std::endl;
		return;
	}

	if (GetHousesOnTile(tile) > 0) {
		std::cout << game_locales_["tile_illegal_has_houses"].get<std::string>() << std::endl;
		return;
	}

	for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
		if (board_.GetTileAt(i)->GetOwner() == tile->GetName()) {
			if (dynamic_cast<Property*>(board_.GetTileAt(i).get()) != nullptr) {
				Property *property = dynamic_cast<Property*>(board_.GetTileAt(i).get());
				if (property->GetTileLevel() >= 2) {
					std::cout << game_locales_["tile_illegal_has_houses_color"].get<std::string>() << std::endl;
					return;
				}
			}
		}
	}

	message = game_locales_["action_sell_tile_confirm"].get<std::string>();
	placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	placeholder = "{{tile_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);

	if (confirm == 'y') {
		player.AddBalance(tile->GetTileCost());
		tile->SetOwner(board_.GetBankName());
		message = game_locales_["action_sell_tile_success"].get<std::string>();
		placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
		placeholder = "{{tile_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));
		std::cout << message << std::endl;

		if (dynamic_cast<Property*>(tile) != nullptr) {
			Property *property = dynamic_cast<Property*>(tile);
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Property*>(board_.GetTileAt(i).get()) != nullptr) {
					Property *other_property = dynamic_cast<Property*>(board_.GetTileAt(i).get());
					if (other_property->GetColourType() == property->GetColourType()) {
						other_property->SetTileLevel(0);
					}
				}
			}
		} else if (dynamic_cast<Railroad*>(tile) != nullptr) {
			int owned_railroads = 0;
			std::vector<int> railroad_group;
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Railroad*>(board_.GetTileAt(i).get()) != nullptr) {
					Railroad *railroad = dynamic_cast<Railroad*>(board_.GetTileAt(i).get());
					if (railroad->GetOwner() == player.GetName()) {
						++owned_railroads;
						railroad_group.push_back(i);
					}
				}
			}
			for (size_t i = 0; i < railroad_group.size(); ++i) {
				Railroad *railroad = dynamic_cast<Railroad*>(board_.GetTileAt(railroad_group[i]).get());
				railroad->SetTileLevel(std::max(owned_railroads - 1, 0));
			}
		} else if (dynamic_cast<Utility*>(tile) != nullptr) {
			int owned_utilities = 0;
			std::vector<int> utility_group;
			for (size_t i = 0; i < board_.GetBoardSize(); ++i) {
				if (dynamic_cast<Utility*>(board_.GetTileAt(i).get()) != nullptr) {
					Utility *utility = dynamic_cast<Utility*>(board_.GetTileAt(i).get());
					if (utility->GetOwner() == player.GetName()) {
						++owned_utilities;
						utility_group.push_back(i);
					}
				}
			}
			for (size_t i = 0; i < utility_group.size(); ++i) {
				Utility *utility = dynamic_cast<Utility*>(board_.GetTileAt(utility_group[i]).get());
				utility->SetTileLevel(std::max(owned_utilities - 1, 0));
			}
		}
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_sell_tile_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
}

void Game::ActionBuyHouse(Player &player)
{
	std::string message = game_locales_["action_buy_house"].get<std::string>();
	std::string placeholder = "{{board_size}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBoardSize()));
	std::cout << message;

	int option;
	std::cin >> option;
	if (option < 1 || option > static_cast<int>(board_.GetBoardSize())) {
		std::cout << game_locales_["tile_illegal"].get<std::string>() << std::endl;
		return;
	}

	Tile *tile = board_.GetTileAt(option - 1).get();

	if (tile->GetOwner() != player.GetName()) {
		std::cout << game_locales_["tile_illegal_not_owned"].get<std::string>() << std::endl;
		return;
	}

	Property *property = dynamic_cast<Property*>(tile);

	if (property == nullptr) {
		std::cout << game_locales_["tile_illegal_not_property"].get<std::string>() << std::endl;
		return;
	}

	if (property->GetTileLevel() > 5) {
		std::cout << game_locales_["tile_illegal_full_houses"].get<std::string>() << std::endl;
		return;
	}

	if (property->GetTileLevel() == 0) {
		std::cout << game_locales_["tile_illegal_not_owned_color"].get<std::string>() << std::endl;
		return;
	}

	int house_cost = GetHouseCost(property);

	if (CanAffordTransaction(player, house_cost) == false) {
		std::cout << game_locales_["tile_illegal_balance"].get<std::string>() << std::endl;
		return;
	}

	message = game_locales_["action_buy_house_confirm"].get<std::string>();
	placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), property->GetName());
	placeholder = "{{house_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);

	if (confirm == 'y') {
		player.AddBalance(-house_cost);
		property->AddBuilding();
		std::string message = game_locales_["action_buy_house_success"].get<std::string>();
		std::string placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
		placeholder = "{{house_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
		std::cout << message << std::endl;
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_buy_house_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
}

void Game::ActionSellHouse(Player &player)
{
	std::string message = game_locales_["action_sell_house"].get<std::string>();
	std::string placeholder = "{{board_size}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(board_.GetBoardSize()));
	std::cout << message;

	int option;
	std::cin >> option;
	if (option < 1 || option > static_cast<int>(board_.GetBoardSize())) {
		std::cout << game_locales_["tile_illegal"].get<std::string>() << std::endl;
		return;
	}

	Tile *tile = board_.GetTileAt(option - 1).get();

	if (tile->GetOwner() != player.GetName()) {
		std::cout << game_locales_["tile_illegal_not_owned"].get<std::string>() << std::endl;
		return;
	}

	Property *property = dynamic_cast<Property*>(tile);

	if (property == nullptr) {
		std::cout << game_locales_["tile_illegal_not_property"].get<std::string>() << std::endl;
		return;
	}

	if (property->GetTileLevel() < 2) {
		std::cout << game_locales_["tile_illegal_no_houses"].get<std::string>() << std::endl;
		return;
	}

	int house_cost = GetHouseCost(property) / 2;

	message = game_locales_["action_sell_house_confirm"].get<std::string>();
	placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), property->GetName());
	placeholder = "{{house_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);

	if (confirm == 'y') {
		player.AddBalance(house_cost);
		property->AddBuilding(-1);
		std::string message = game_locales_["action_sell_house_success"].get<std::string>();
		std::string placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), property->GetName());
		placeholder = "{{house_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
		std::cout << message << std::endl;
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_sell_house_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
}

bool Game::ActionEndTurn(Player &player)
{
	std::string message, placeholder;
	if (player.GetBalance() < 0) {
		message = game_locales_["action_end_turn_warn_balance"].get<std::string>();
		std::cout << message << std::endl;
	}

	message = game_locales_["action_end_turn_confirm"].get<std::string>();
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);

	if (confirm == 'y') {
		return true;
	}
	return false;
}

// Clear screen
// !voi incerca sa invat sa folosesc rlutil pt primul release; momentan 
// !il voi lasa asa ca sa pot lucra si testa
void Game::ClearScreen()
{
	#ifdef WINDOWS
    		std::system("cls");
	#else
		std::system ("clear");
	#endif
}

// Operator Overloads (nu stiu ce altceva sa pun aici; pt tema 1)
std::ostream &operator<<(std::ostream &os, const Game &game)
{
	os << game.board_ << std::endl;
	os << game.chance_deck_ << std::endl;
	os << game.community_deck_ << std::endl;
	os << game.dice_ << std::endl;
	for (const Player &player : game.players_) {
		os << player << std::endl;
	}

	return os;
}