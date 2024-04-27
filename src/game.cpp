#include "game.hpp"

// Constructor and Destructor
Game::Game() {};
Game::~Game() {};

// Game methods
void Game::InitGame()
{
	// Choose language
	do {
		std::cout << "Choose language (en): ";
		std::cin >> language_;
		if (language_ != "en") {
			std::cout << "Language not supported yet." << std::endl;
		}
	} while (language_ != "en");

	// Init board
	board_.InitBoard(language_);

	// Load locales
	InitLocales();

	// Welcome message
	std::string message = game_locales_["welcome"].get<std::string>();
	std::cout << message << std::endl;

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
			//PlayTurn(i);
			if (players_[i].GetBalance() < 0) {
				RemovePlayer(i);
				--i;
			}
		}
	}

	// End game
	EndGame(winner_index);
}

void Game::EndGame(const int winner_index)
{
	std::string message = game_locales_["winner"].get<std::string>();
	std::string placeholder = "{{winner}}";
	message.replace(message.find(placeholder), placeholder.length(), players_[winner_index].GetName());
	std::cout << message << std::endl;

	message = game_locales_["thanks"].get<std::string>();
	placeholder = "{{nl}}";
	message.replace(message.find(placeholder), placeholder.length(), "\n");
	std::cout << message << std::endl;
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
			std::cout << player_locales_["invalid_count"].get<std::string>() << std::endl;
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

		AddPlayer(Player(name));
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
		std::cout << message << std::endl;
		return false;
	}
	if (name.length() > max_name_length_) {
		std::string message = player_locales_["long_name"].get<std::string>();
		std::string placeholder = "{{max}}";
		message.replace(message.find(placeholder), placeholder.length(), std::to_string(max_name_length_));
		std::cout << message << std::endl;
		return false;
	}
	if (name_copy == "BANK") {
		std::cout << player_locales_["bank_name"].get<std::string>() << std::endl;
		return false;
	}
	for (const auto &player : players_) {
		std::string player_name = player.GetName();
		std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::toupper);
		if (name_copy == player_name) {
			std::cout << player_locales_["duplicate_name"].get<std::string>() << std::endl;
			return false;
		}
	}
	return true;
}

void Game::AddPlayer(const Player &player)
{
	players_.push_back(player);
}

void Game::RemovePlayer(const int player_index)
{
	std::string message = player_locales_["remove_player"].get<std::string>();
	std::string placeholder = "{{player}}";
	message.replace(message.find(placeholder), placeholder.length(), players_[player_index].GetName());
	std::cout << message << std::endl;

	players_.erase(players_.begin() + player_index);
}