#include "game.hpp"

// Constructor
Game::Game(const std::string &language, const int dice_min, const int dice_max, const int player_start_balance, 
	const size_t min_players, const size_t max_players, const size_t min_name_length, const size_t max_name_length, 
	const int chance_deck_size, const int community_deck_size, const int bail_value, const std::string &bank_name)
	: board_(bail_value, bank_name, "../locales/" + language + "tiles.json"), chance_deck_(language, "chance", chance_deck_size),
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
		std::cout << std::endl;
		PrintBlank();

		switch (option) {
		case 'i':
			ActionInfo();
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
		case 'r':
			ClearScreen();
			PrintBlank();
			dice_values = ActionRollDice();
			PrintBlank();
			std::cout << std::endl << std::endl;
			break;
		case 'q':
			bool quit_confirm = ActionQuitGame(player);
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
	PrintBlank();
	if (dice_values.first == dice_values.second) {
		player.AddDoubleCount(1);
		if (player.GetDoubleCount() == 3) {
			std::cout << game_locales_["action_roll_dice_double_jail"].get<std::string>() << std::endl;
			PrintBlank();
			std::cout << std::endl << std::endl;
			player.GoToJail();
			return;
		} else {
			can_roll_again = true;
			std::cout << game_locales_["action_roll_dice_double_safe"].get<std::string>() << std::endl;
		}
	}

	// Move player
	MovePlayerBy(player, dice_values.first + dice_values.second);
	Tile *tile = board_.GetTileAt(player.GetPosition()).get();
	std::string message = game_locales_["action_move"].get<std::string>();
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	std::cout << message << std::endl;

	// Tile action
	
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
		MovePlayerAt(players_[i], 0);
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

	for (int i = 0; i < board_.GetBoardSize(); ++i) {
		if (board_.GetTileAt(i)->GetOwner() == player.GetName()) {
			board_.InitTile(i);
		}
	}

	players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
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
	std::cout << std::endl;

	if (ready == 'y') {
		return true;
	}
	return false;
}

// Board methods
void Game::MovePlayerAt(Player &player, const int position)
{
	board_.GetTileAt(player.GetPosition())->RemovePlayerHere(player.GetName());
	board_.GetTileAt(position)->AddPlayerHere(player.GetName());
	player.SetPosition(position);
}

void Game::MovePlayerBy(Player &player, const int steps)
{
	int new_position = player.GetPosition() + steps;
	if (new_position >= board_.GetBoardSize()) {
		new_position -= board_.GetBoardSize();
		int pass_go = dynamic_cast<Go*>(board_.GetTileAt(0).get())->GetPassGoAmount();
		player.AddBalance(pass_go);
	
	}
	MovePlayerAt(player, new_position);
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
		if (property->GetTileLevel() > 2) {
			return property->GetTileLevel() - 2;
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

void Game::AddHouseToTile(Tile *tile, const int amount)
{
	if (dynamic_cast<Property*>(tile) != nullptr) {
		Property *property = dynamic_cast<Property*>(tile);
		property->AddBuilding(amount);
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

	if (dice_values.first == dice_values.second) {
		message = game_locales_["action_roll_dice_double"].get<std::string>();
		std::cout << message << std::endl;
	}

	return dice_values;
}

bool Game::ActionQuitGame(Player &player)
{
	std::string message = game_locales_["action_quit_game"].get<std::string>();
	std::cout << message;

	char quit;
	std::cin >> quit;
	quit = std::tolower(quit);
	std::cout << std::endl;

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
	confirm = std::tolower(confirm);
	std::cout << std::endl;

	if (confirm == 'y') {
		player.AddBalance(-tile->GetTileCost());
		tile->SetOwner(player.GetName());
		std::cout << game_locales_["action_buy_tile_success"].get<std::string>() << std::endl;
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
	std::cout << std::endl;
	if (option < 1 || option > board_.GetBoardSize()) {
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

	std::cout << game_locales_["action_sell_tile_confirm"].get<std::string>() << std::endl;
	placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	placeholder = "{{tile_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);
	std::cout << std::endl;

	if (confirm == 'y') {
		player.AddBalance(tile->GetTileCost());
		tile->SetOwner(board_.GetBankName());
		std::cout << game_locales_["action_sell_tile_success"].get<std::string>() << std::endl;
		placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
		placeholder = "{{tile_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(tile->GetTileCost()));
		std::cout << message << std::endl;
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_sell_tile_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
}

void Game::ActionBuyHouse(Player &player)
{
	std::string message = game_locales_["action_buy_house"].get<std::string>();
	std::cout << message;

	int option;
	std::cin >> option;
	std::cout << std::endl;
	if (option < 1 || option > board_.GetBoardSize()) {
		std::cout << game_locales_["tile_illegal"].get<std::string>() << std::endl;
		return;
	}

	Tile *tile = board_.GetTileAt(option - 1).get();

	if (tile->GetOwner() != player.GetName()) {
		std::cout << game_locales_["tile_illegal_not_owned"].get<std::string>() << std::endl;
		return;
	}

	if (GetHousesOnTile(tile) > 4) {
		std::cout << game_locales_["tile_illegal_full_houses"].get<std::string>() << std::endl;
		return;
	}

	int house_cost = GetHouseCost(tile);

	if (CanAffordTransaction(player, house_cost) == false) {
		std::cout << game_locales_["tile_illegal_balance"].get<std::string>() << std::endl;
		return;
	}

	std::cout << game_locales_["action_buy_house_confirm"].get<std::string>() << std::endl;
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	placeholder = "{{house_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);
	std::cout << std::endl;

	if (confirm == 'y') {
		player.AddBalance(-house_cost);
		AddHouseToTile(tile, 1);
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
	std::cout << message;

	int option;
	std::cin >> option;
	std::cout << std::endl;
	if (option < 1 || option > board_.GetBoardSize()) {
		std::cout << game_locales_["tile_illegal"].get<std::string>() << std::endl;
		return;
	}

	Tile *tile = board_.GetTileAt(option - 1).get();

	if (tile->GetOwner() != player.GetName()) {
		std::cout << game_locales_["tile_illegal_not_owned"].get<std::string>() << std::endl;
		return;
	}

	if (GetHousesOnTile(tile) < 1) {
		std::cout << game_locales_["tile_illegal_no_houses"].get<std::string>() << std::endl;
		return;
	}

	int house_cost = GetHouseCost(tile) / 2;

	std::cout << game_locales_["action_sell_house_confirm"].get<std::string>() << std::endl;
	std::string placeholder = "{{tile_name}}";
	message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
	placeholder = "{{house_price}}";
	message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
	std::cout << message;

	char confirm;
	std::cin >> confirm;
	confirm = std::tolower(confirm);
	std::cout << std::endl;

	if (confirm == 'y') {
		player.AddBalance(house_cost);
		AddHouseToTile(tile, -1);
		std::string message = game_locales_["action_sell_house_success"].get<std::string>();
		std::string placeholder = "{{tile_name}}";
		message.replace(message.find(placeholder), placeholder.length(), tile->GetName());
		placeholder = "{{house_price}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(house_cost));
		std::cout << message << std::endl;
	} else if (confirm == 'n') {
		std::cout << game_locales_["action_sell_house_cancel"].get<std::string>() << std::endl;
	} else {
		PrintOptionIllegal();
	}
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