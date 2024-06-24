#include "custom_except.hpp"
#include "game.hpp"
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

int main()
{	
	std::string language;
	std::cout << "Choose language (en): ";
	std::cin >> language;

	if (language != "en") {
		throw InvalidLanguage();
	}

	std::string system_locales_path = "locales/" + language + "/system.json";
	std::ifstream system_locales_file(system_locales_path);
	if (!system_locales_file.is_open()) {
		throw FileNotFound(system_locales_path);
	}
	nlohmann::json system_locales;
	system_locales_file >> system_locales;
	system_locales_file.close();

	int dice_min = system_locales["dice_min"].get<int>();
	int dice_max = system_locales["dice_max"].get<int>();
	int player_start_balance = system_locales["player_start_balance"].get<int>();
	size_t min_players = system_locales["min_players"].get<size_t>();
	size_t max_players = system_locales["max_players"].get<size_t>();
	size_t min_name_length = system_locales["min_name_length"].get<size_t>();
	size_t max_name_length = system_locales["max_name_length"].get<size_t>();
	int chance_deck_size = system_locales["chance_deck_size"].get<int>();
	int community_deck_size = system_locales["community_deck_size"].get<int>();
	int bail_value = system_locales["bail_value"].get<int>();
	std::string bank_name = system_locales["bank_name"].get<std::string>();

	Game &game = Game::GetInstance(language, dice_min, dice_max, player_start_balance, min_players, max_players, min_name_length, max_name_length, chance_deck_size, community_deck_size, bail_value, bank_name);
	(void)game;

	return 0;
}