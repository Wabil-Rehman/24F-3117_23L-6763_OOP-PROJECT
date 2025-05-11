#include "Stronghold.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Player::Player() : id(-1), name(""), society(nullptr), population(nullptr), army(nullptr),
leadership(nullptr), bank(nullptr), resources(nullptr), economy(nullptr) {
}

Player::~Player() {}

Game::Game() {
    numPlayers = 0;
    communication = new Communication();
    diplomacy = new Diplomacy();
    market = new Market();
    conflict = new Conflict();
    map = new Map();
    event = new Event();
    currentTurn = 1;
    endGame = false;
}

void Game::initialize() {
    cout << "Enter number of players (2-4): ";
    cin >> numPlayers;
    if (numPlayers < 2 || numPlayers > MAX_PLAYERS) {
        cout << "Invalid number of players. Defaulting to 2.\n";
        numPlayers = 2;
    }
    cin.ignore();
    for (int i = 0; i < numPlayers; i++) {
        players[i].id = i;
        cout << "Enter name for Player " << i + 1 << ": ";
        getline(cin, players[i].name);
        players[i].society = new Society();
        players[i].population = new Population();
        players[i].army = new Army();
        players[i].leadership = new Leadership();
        players[i].bank = new Bank();
        players[i].resources = new Resources();
        players[i].economy = new Economy();
    }
    map->initialize(players, numPlayers);
}

void Game::playTurn(int playerId) {
    cout << "\n=== Turn " << currentTurn << " - Player " << players[playerId].name << " ===\n";
    int choice;
    do {
        cout << "\n------------ Menu ------------\n";
        cout << "1. View Society\n";
        cout << "2. Update Population\n";
        cout << "3. Manage Army\n";
        cout << "4. Change Leadership\n";
        cout << "5. Manage Bank\n";
        cout << "6. Manage Resources\n";
        cout << "7. Manage Economy\n";
        cout << "8. Send Message\n";
        cout << "9. View Messages\n";
        cout << "10. Propose Treaty\n";
        cout << "11. View Treaties\n";
        cout << "12. Propose Trade\n";
        cout << "13. View/Accept Trade Offers\n";
        cout << "14. Declare War\n";
        cout << "15. View Map\n";
        cout << "16. Move on Map\n";
        cout << "17. End Turn\n";
        cout << "18. Quit Game\n";
		cout << "------------------------------\n";
        cout << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            players[playerId].society->displaySociety();
            break;
        case 2: {
            int food, shelter;
            bool war;
            cout << "Enter food supply (0-100): ";
            cin >> food;
            cout << "Enter shelter level (0-100): ";
            cin >> shelter;
            cout << "Is there war? (1-Yes / 0-No): ";
            cin >> war;
            cin.ignore();
            players[playerId].population->updatePopulation(food, shelter, war);
            players[playerId].population->displayPopulation();
            break;
        }
        case 3: {
            int recruits, rations;
            cout << "Enter number of recruits (0-100): ";
            cin >> recruits;
            cout << "Enter rations to feed (0-200): ";
            cin >> rations;
            cin.ignore();
            players[playerId].army->recruit(recruits, players[playerId].population);
            players[playerId].army->train();
            players[playerId].army->feed(rations);
            players[playerId].army->displayArmy();
            break;
        }
        case 4: {
            string name, policy;
            cout << "Enter new leader name: ";
            getline(cin, name);
            cout << "Enter policy direction (e.g. Peace/War): ";
            getline(cin, policy);
            players[playerId].leadership->electNewLeader(name);
            players[playerId].leadership->changePolicy(policy);
            players[playerId].leadership->displayLeadership();
            break;
        }
        case 5: {
            float loan, repay;
            cout << "Enter loan amount to take: ";
            cin >> loan;
            cout << "Enter loan amount to repay: ";
            cin >> repay;
            cin.ignore();
            players[playerId].bank->takeLoan(loan);
            players[playerId].bank->repayLoan(repay);
            players[playerId].bank->audit();
            players[playerId].bank->displayBank();
            break;
        }
        case 6: {
            int f, w, s, i;
            cout << "Enter food to gather: ";
            cin >> f;
            cout << "Enter wood to gather: ";
            cin >> w;
            cout << "Enter stone to gather: ";
            cin >> s;
            cout << "Enter iron to gather: ";
            cin >> i;
            cin.ignore();
            players[playerId].resources->gatherResources(f, w, s, i);
            players[playerId].resources->displayResources();
            break;
        }
        case 7: {
            float expenditure;
            cout << "Enter expenditure amount: ";
            cin >> expenditure;
            cin.ignore();
            players[playerId].economy->collectTaxes(players[playerId].population->getTotal());
            players[playerId].economy->updateExpenditure(expenditure);
            players[playerId].economy->audit();
            players[playerId].economy->displayEconomy();
            break;
        }
        case 8: {
            int recipientId;
            string content;
            cout << "Enter recipient player ID (0-" << numPlayers - 1 << "): ";
            cin >> recipientId;
            cin.ignore();
            cout << "Enter message: ";
            getline(cin, content);
            communication->sendMessage(playerId, recipientId, content);
            break;
        }
        case 9:
            communication->viewMessages(playerId);
            break;
        case 10: {
            int otherPlayerId;
            string type;
            int duration;
            cout << "Enter other player ID (0-" << numPlayers - 1 << "): ";
            cin >> otherPlayerId;
            cin.ignore();
            cout << "Enter treaty type (Alliance/Non-Aggression/Trade): ";
            getline(cin, type);
            cout << "Enter duration (turns): ";
            cin >> duration;
            cin.ignore();
            diplomacy->proposeTreaty(playerId, otherPlayerId, type, duration);
            break;
        }
        case 11:
            diplomacy->displayTreaties(playerId);
            break;
        case 12: {
            int recipientId, offerF, offerW, offerS, offerI, requestF, requestW, requestS, requestI;
            bool smuggling;
            cout << "Enter recipient player ID (0-" << numPlayers - 1 << "): ";
            cin >> recipientId;
            cout << "Enter food to offer: ";
            cin >> offerF;
            cout << "Enter wood to offer: ";
            cin >> offerW;
            cout << "Enter stone to offer: ";
            cin >> offerS;
            cout << "Enter iron to offer: ";
            cin >> offerI;
            cout << "Enter food requested: ";
            cin >> requestF;
            cout << "Enter wood requested: ";
            cin >> requestW;
            cout << "Enter stone requested: ";
            cin >> requestS;
            cout << "Enter iron requested: ";
            cin >> requestI;
            cout << "Is this smuggling? (1-Yes / 0-No): ";
            cin >> smuggling;
            cin.ignore();
            market->proposeTrade(playerId, recipientId, offerF, offerW, offerS, offerI,
                requestF, requestW, requestS, requestI, smuggling);
            break;
        }
        case 13: {
            market->viewOffers(playerId);
            int offerIndex;
            cout << "Enter offer index to accept (-1 to skip): ";
            cin >> offerIndex;
            cin.ignore();
            if (offerIndex >= 0) {
                market->acceptTrade(offerIndex, players, diplomacy);
            }
            break;
        }
        case 14: {
            int defenderId;
            cout << "Enter defender player ID (0-" << numPlayers - 1 << "): ";
            cin >> defenderId;
            cin.ignore();
            conflict->declareWar(playerId, defenderId, players, diplomacy, map);
            break;
        }
        case 15:
            map->displayMap(playerId);
            break;
        case 16: {
            int newX, newY;
            cout << "Enter new X coordinate (0-4): ";
            cin >> newX;
            cout << "Enter new Y coordinate (0-4): ";
            cin >> newY;
            cin.ignore();
            map->movePlayer(playerId, newX, newY);
            break;
        }
        case 17:
            cout << "Ending turn for Player " << players[playerId].name << ".\n";
            currentTurn++;
            break;
        case 18:
            cout << "Quitting game. Saving state...\n";
            saveGame();
            endGame = true;
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 17 && !endGame);
}

void Game::saveGame() {
    ofstream outFile("save_game.txt");
    if (outFile.is_open()) {
        outFile << "# Game State\n";
        outFile << "NumPlayers: " << numPlayers << "\n";
        outFile << "CurrentTurn: " << currentTurn << "\n\n";
        for (int i = 0; i < numPlayers; i++) {
            outFile << "# Player " << i << "\n";
            outFile << "Name: " << players[i].name << "\n";
            players[i].society->saveToFile(outFile);
            players[i].population->saveToFile(outFile);
            players[i].army->saveToFile(outFile);
            players[i].leadership->saveToFile(outFile);
            players[i].bank->saveToFile(outFile);
            players[i].resources->saveToFile(outFile);
            players[i].economy->saveToFile(outFile);
            outFile << "\n";
        }
        communication->saveToFile(outFile);
        diplomacy->saveToFile(outFile);
        market->saveToFile(outFile);
        map->saveToFile(outFile);
        cout << "Game saved successfully.\n";
    }
    else {
        cout << "Error saving game.\n";
    }
    outFile.close();
}

void Game::loadGame() {
    ifstream inFile("save_game.txt");
    if (inFile.is_open()) {
        string line;
        bool oldFormat = false;

        getline(inFile, line);
        inFile.seekg(0);
        if (line[0] >= '0' && line[0] <= '9') {
            oldFormat = true;
            inFile >> numPlayers >> currentTurn;
            inFile.ignore();
        }
        else {
            while (getline(inFile, line)) {
                if (line.find("NumPlayers:") == 0) {
                    size_t colonPos = line.find(":");
                    if (colonPos != string::npos) {
                        numPlayers = stoi(line.substr(colonPos + 1));
                    }
                    else {
                        cout << "Error: Malformed NumPlayers line.\n";
                        numPlayers = 0;
                    }
                }
                else if (line.find("CurrentTurn:") == 0) {
                    size_t colonPos = line.find(":");
                    if (colonPos != string::npos) {
                        currentTurn = stoi(line.substr(colonPos + 1));
                    }
                    else {
                        cout << "Error: Malformed CurrentTurn line.\n";
                        currentTurn = 1; 
                    }
                    break;
                }
            }
        }
        if (numPlayers < 2 || numPlayers > MAX_PLAYERS) {
            cout << "Invalid save data. Starting new game.\n";
            initialize();
            inFile.close();
            return;
        }

        // Load player data
        for (int i = 0; i < numPlayers; i++) {
            players[i].id = i;
            players[i].society = new Society();
            players[i].population = new Population();
            players[i].army = new Army();
            players[i].leadership = new Leadership();
            players[i].bank = new Bank();
            players[i].resources = new Resources();
            players[i].economy = new Economy();

            if (oldFormat) {
                getline(inFile, players[i].name);
            }
            else {
                while (getline(inFile, line)) {
                    if (line.find("Name:") == 0) {
                        players[i].name = line.substr(6); 
                        break;
                    }
                }
            }

            players[i].society->loadFromFile(inFile);
            players[i].population->loadFromFile(inFile);
            players[i].army->loadFromFile(inFile);
            players[i].leadership->loadFromFile(inFile);
            players[i].bank->loadFromFile(inFile);
            players[i].resources->loadFromFile(inFile);
            players[i].economy->loadFromFile(inFile);
        }

        communication->loadFromFile(inFile);
        diplomacy->loadFromFile(inFile);
        market->loadFromFile(inFile);
        map->loadFromFile(inFile);

        cout << "Game loaded successfully.\n";
    }
    else {
        cout << "No save file found, starting a new game.\n";
        initialize();
    }
    inFile.close();
}


Game::~Game() {
    for (int i = 0; i < numPlayers; i++) {
        delete players[i].society;
        delete players[i].population;
        delete players[i].army;
        delete players[i].leadership;
        delete players[i].bank;
        delete players[i].resources;
        delete players[i].economy;
    }
    delete communication;
    delete diplomacy;
    delete market;
    delete conflict;
    delete map;
    delete event;
    cout << "Game destroyed.\n";
}