#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <random>

#define INT_LIM 2147483647

std::string StringToUpper(std::string word) {
    size_t length = word.length();
    for(size_t i = 0; i < length; i++) {
        char tempc = word[i];
        int tempi = tempc > 96 && tempc < 123;
        word[i] = tempc * !tempi + (tempc - 32) * tempi;
    }

    return word;
}

class Player {
private:
    bool active;
    std::string name;
    int money;
    int properties_owned[40];
    int gooj_card_count;
    bool in_jail;
    int doubles_rolled;

public:
    Player() {};

    Player(std::string name) {
        this->name = name;
        this->active = true;
        this->money = 1500;
        this->gooj_card_count = 0;
        this->in_jail = false;
        this->doubles_rolled = 0;

        for(int i = 0; i < 40; i++) {
            properties_owned[i] = -1;
        }

        if(name == "Bank") {
            this->money = INT_LIM;
        }
    }

    std::string getName() {
        return this->name;
    }

    void payFine(int sum) {
        this->money -= sum;
    }

    int getJailed() {
        return this->in_jail;
    }

    void setJailed(bool in_jail) {
        this->in_jail = in_jail;
    }

    int getGoojCards() {
        return this->gooj_card_count;
    }

    void setGoojCards(int gooj_card_count) {
        this->gooj_card_count = gooj_card_count;
    }

    int getDoubles() {
        return this->doubles_rolled;
    }

    void setDoubles(int doubles_count) {
        this->doubles_rolled = doubles_count;
    }

};

class Tile {
private:
    std::string name;
    std::string type;
    std::string colour;
    int owner;
    int tile_cost;
    int property_cost;
    std::array<int, 7> rents;       //0 = tile bought, 1 = all colour owned, 2-5 = houses, 6 = hotel

public:
    Tile() {};

    Tile(std::string name, std::string type, std::string colour, int tile_cost, int property_cost, std::array<int, 7> rents) {
        this->name = name;
        this->type = type;
        this->colour = colour;
        this->owner = 0;
        this->tile_cost = tile_cost;
        this->property_cost = property_cost;
        this->rents = rents;
    }
};

class Board {
private:
    Tile tiles[40];
    Player players[9];      // Bank will be player 0

public:
    Board() {};

    void StartGame() {
        int player_count = GetPlayerCount();

        players[0] = Player("Bank");

        for(int i = 1; i <= player_count; i++) {
            players[i] = Player(InitializePlayer(i));
        }

        std::string tile_names[40] = {
            "Go", "Mediterranean Avenue", "Community Chest", "Baltic Avenue", "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance", "Vermont Avenue", "Connecticut Avenue",
            "Jail", "St. Charles Place", "Electric Company", "States Avenue", "Virginia Avenue", "Pennsylvania Railroad", "St. James Place", "Community Chest", "Tennessee Avenue", "New York Avenue",
            "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue", "Illinois Avenue", "B. & O. Railroad", "Atlantic Avenue", "Ventnor Avenue", "Water Works", "Marvin Gardens",
            "Go to Jail", "Pacific Avenue", "North Carolina Avenue", "Community Chest", "Pennsylvania Avenue", "Short Line", "Chance", "Park Place", "Luxury Tax", "Boardwalk"
        };
        std::string tile_types[40] = {
            "Go", "Property", "Community Chest", "Property", "Tax", "Railroad", "Property", "Chance", "Property", "Property",
            "Jail", "Property", "Utility", "Property", "Property", "Railroad", "Property", "Community Chest", "Property", "Property",
            "Free Parking", "Property", "Chance", "Property", "Property", "Railroad", "Property", "Property", "Utility", "Property",
            "Go to Jail", "Property", "Property", "Community Chest", "Property", "Railroad", "Chance", "Property", "Tax", "Property"
        };
        std::string tile_colours[40] = {
            "None", "Brown", "None", "Brown", "None", "None", "Light Blue", "None", "Light Blue", "Light Blue",
            "None", "Pink", "None", "Pink", "Pink", "None", "Orange", "None", "Orange", "Orange",
            "None", "Red", "None", "Red", "Red", "None", "Yellow", "Yellow", "None", "Yellow",
            "None", "Green", "Green", "None", "Green", "None", "None", "Blue", "None", "Blue"
        };
        int tile_costs[40] = {
            0, 60, 0, 60, 0, 200, 100, 0, 100, 120,
            0, 140, 150, 140, 160, 200, 180, 0, 180, 200,
            0, 220, 0, 220, 240, 200, 260, 260, 150, 280,
            0, 300, 300, 0, 320, 200, 0, 350, 0, 400
        };
        int property_costs[40] = {
            0, 50, 0, 50, 0, 0, 50, 0, 50, 50,
            0, 100, 150, 100, 100, 0, 100, 0, 100, 100,
            0, 150, 0, 150, 150, 0, 150, 150, 0, 150,
            0, 200, 200, 0, 200, 0, 0, 200, 0, 200
        };
        std::array<int, 7> tile_rents[40] = {
            {0, 0, 0, 0, 0, 0, 0}, {2, 4, 10, 30, 90, 160, 250}, {0, 0, 0, 0, 0, 0, 0}, {4, 8, 20, 60, 180, 320, 450}, {0, 0, 0, 0, 0, 0, 0}, {25, 50, 100, 200, 0, 0, 0}, {6, 12, 30, 90, 270, 400, 550}, {0, 0, 0, 0, 0, 0, 0}, {6, 12, 30, 90, 270, 400, 550}, {8, 16, 40, 100, 300, 450, 600},
            {0, 0, 0, 0, 0, 0, 0}, {10, 20, 50, 150, 450, 625, 750}, {0, 0, 0, 0, 0, 0, 0}, {10, 20, 50, 150, 450, 625, 750}, {12, 24, 60, 180, 500, 700, 900}, {25, 50, 100, 200, 0, 0, 0}, {14, 28, 70, 200, 550, 750, 950}, {0, 0, 0, 0, 0, 0, 0}, {14, 28, 70, 200, 550, 750, 950}, {16, 32, 80, 220, 600, 800, 1000},
            {0, 0, 0, 0, 0, 0, 0}, {18, 36, 90, 250, 700, 875, 1050}, {0, 0, 0, 0, 0, 0, 0}, {18, 36, 90, 250, 700, 875, 1050}, {20, 40, 100, 300, 750, 925, 1100}, {25, 50, 100, 200, 0, 0, 0}, {22, 44, 110, 330, 800, 975, 1150}, {22, 44, 110, 330, 800, 975, 1150}, {0, 0, 0, 0, 0, 0, 0}, {24, 48, 120, 360, 850, 1025, 1200},
            {0, 0, 0, 0, 0, 0, 0}, {26, 52, 130, 390, 900, 1100, 1275}, {26, 52, 130, 390, 900, 1100, 1275}, {0, 0, 0, 0, 0, 0, 0}, {28, 56, 150, 450, 1000, 1200, 1400}, {25, 50, 100, 200, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {35, 70, 175, 500, 1100, 1300, 1500}, {0, 0, 0, 0, 0, 0, 0}, {50, 100, 200, 600, 1400, 1700, 2000}
        };

        for(int i = 0; i < 40; i++) {
            tiles[i] = Tile(tile_names[i], tile_types[i], tile_colours[i], tile_costs[i], property_costs[i], tile_rents[i]);
        }

        while(1) {
            for(int i = 1; i <= player_count; i++) {
                std::cout << players[i].getName() << ", it is your turn!" << std::endl;
                std::cout << "Press enter when you are ready..." << std::endl;
                std::cin.ignore();
                std::cin.get();
                PromptPlayer(i);
            }
        }
    }

    int GetPlayerCount() {
        std::cout << "Hello dear tester! Welcome to this implementation of a totally original game." << std::endl;
        
        while(1) {
            std::cout << "How many players would you like to initialize? ";
            int player_count;
            std::cin >> player_count;
            std::cout << std::endl;

            if(player_count < 2) {
                std::cout << "Not enough players! Please try again..." << std::endl;
                continue;
            }
            if(player_count > 8) {
                std::cout << "Too many players! You have a lot of friends, don't you? Please try again..." << std::endl;
                continue;
            }
            
            std::cout << "Great choice! The game shall commence...";

            return player_count;
        }
    }
    
    std::string InitializePlayer(int idx) {
        while(1) {
            std::cout << "Enter the name of player " << idx << ": ";
            std::string player_name;
            std::cin >> player_name;
            std::cout << std::endl;

            if(StringToUpper(player_name) == "BANK") {
                std::cout << "Illegal name! Please choose a different name..." << std::endl;
                continue;
            }

            return player_name; 
        }
    }

    int RollDice() {
        std::random_device                  rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_int_distribution<int>  distr(1, 6);

        return distr(generator);
    }

    void PromptPlayer(int current_player) {
        if(players[current_player].getJailed() == true) {
            ResolveJail(current_player);
            return;
        }

        int roll1 = RollDice();
        int roll2 = RollDice();
        int roll = roll1 + roll2;
    }

    void ResolveJail(int current_player) {
        bool has_gooj_card = (players[current_player].getGoojCards() > 0);
        bool can_roll_doubles = (players[current_player].getDoubles() < 3);
        std::cout << "Uh oh! You are in jail! Your options are: " << std::endl;
        std::cout << " 1) Pay a $50 fine" << std::endl;
        std::cout << " 2) Use a 'Get out of Jail Free' card (you have " << players[current_player].getGoojCards() << " cards)" << std::endl;
        std::cout << " 3) Attempt to roll a double (tries left: " << 3 - players[current_player].getDoubles() << ")" << std::endl;
        std::cout << "What will you do? (1";
        //todo: attempt to buy card from other player, attempt to sell property to pay fine if bal < 50

        if(has_gooj_card) {
            std::cout << "/2";
        }
        if(can_roll_doubles) {
            std::cout << "/3";
        }

        std::cout << ") ";
        int option;
        std::cin >> option;
        
        switch(option) {
            case 1: {
                players[current_player].payFine(50);
                break;
            }
            case 2: {
                if(has_gooj_card == false) {
                    std::cout << "Oops! You have no Get out of Jail Free cards. Try something else..." << std::endl;
                    ResolveJail(current_player);
                    return;
                }
                players[current_player].setGoojCards(players[current_player].getGoojCards() - 1);
                break;
            }
            case 3: {
                if(can_roll_doubles == false) {
                    std::cout << "Oops! You have no rolls left. Try something else..." << std::endl;
                    ResolveJail(current_player);
                    return;
                }
                int roll1 = RollDice();
                int roll2 = RollDice();
                int roll = roll1 + roll2;

                if(roll1 == roll2) {
                    std::cout << "Phew! You rolled a double (" << roll1 << ") and have escaped jail! Enjoy your freedom (while it lasts)..." << std::endl;
                    players[current_player].setDoubles(0);
                    players[current_player].moveBy(roll);
                }
                else {
                    std::cout << "You rolled " << roll1 << " and " << roll2 << ". You will still be in jail." << std::endl;
                    players[current_player].setDoubles(players[current_player].getDoubles() + 1);
                }
                break;
            }
            default: {
                std::cout << "Illegal input!" << std::endl;
                ResolveJail(current_player);
                break;
            }
        }
    }
};

int main() {
    Board board;
    board.StartGame();

    return 0;
}