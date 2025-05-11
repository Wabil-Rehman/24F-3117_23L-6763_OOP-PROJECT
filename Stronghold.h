#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ============================== Forward Declarations ==============================
class Society;
class Population;
class Army;
class Leadership;
class Bank;
class Resources;
class Economy;
class Event;
class Communication;
class Diplomacy;
class Market;
class Conflict;
class Map;
class Game;

// ============================== Player Struct ==============================
struct Player {
    int id;
    string name;
    Society* society;
    Population* population;
    Army* army;
    Leadership* leadership;
    Bank* bank;
    Resources* resources;
    Economy* economy;
    Player();
    ~Player();
};

// ============================== Message Struct ==============================
struct Message {
    int senderId;
    int recipientId;
    string content;
    bool active;
    Message();
};

// ============================== Treaty Struct ==============================
struct Treaty {
    int player1Id;
    int player2Id;
    string type; // "Alliance", "Non-Aggression", "Trade"
    int duration; // Turns remaining
    bool active;
    Treaty();
};

// ============================== TradeOffer Struct ==============================
struct TradeOffer {
    int senderId;
    int recipientId;
    int offerFood, offerWood, offerStone, offerIron;
    int requestFood, requestWood, requestStone, requestIron;
    bool smuggling; // True for black-market trade
    bool active;
    TradeOffer();
};

// ============================== Society Class ==============================
class Society {
private:
    int peasants;
    int merchants;
    int nobles;
public:
    Society();
    void displaySociety();
    void manageConflict();
    void adjustClass(int peasants, int merchants, int nobles);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Society();
};

// ============================== Population Class ==============================
class Population {
private:
    int total;
    int sick;
    int rebels;
public:
    Population();
    void updatePopulation(int foodSupply, int shelter, bool war);
    void displayPopulation();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    int getTotal() { return total; }
    void setTotal(int newTotal) { total = max(0, newTotal); }
    ~Population();
};

// ============================== Army Class ==============================
class Army {
private:
    int soldiers;
    int trained;
    int morale;
    int food;
public:
    Army();
    void recruit(int people, Population* pop);
    void train();
    void feed(int rations);
    void displayArmy();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    int getSoldiers() { return soldiers; }
    int getTrained() { return trained; }
    int getMorale() { return morale; }
    void reduceSoldiers(int amount) { soldiers = max(0, soldiers - amount); }
    void reduceMorale(int amount) { morale = max(0, morale - amount); }
    ~Army();
};

// ============================== Leadership Class ==============================
class Leadership {
private:
    string currentLeader;
    string policy;
    int approval;
public:
    Leadership();
    void electNewLeader(string name);
    void changePolicy(string newPolicy);
    void displayLeadership();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    void reduceApproval(int amount) { approval = max(0, approval - amount); }
    ~Leadership();
};

// ============================== Bank Class ==============================
class Bank {
private:
    float treasury;
    float loanDebt;
    float interestRate;
public:
    Bank();
    void takeLoan(float amount);
    void repayLoan(float amount);
    void audit();
    void displayBank();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    float getTreasury() { return treasury; }
    void addTreasury(float amount) { treasury += amount; }
    void reduceTreasury(float amount) { treasury = max(0.0f, treasury - amount); }
    ~Bank();
};

// ============================== Resources Class ==============================
class Resources {
private:
    int food;
    int wood;
    int stone;
    int iron;
public:
    Resources();
    void gatherResources(int f, int w, int s, int i);
    void consumeResources(int f, int w, int s, int i);
    void displayResources();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    int getFood() { return food; }
    int getWood() { return wood; }
    int getStone() { return stone; }
    int getIron() { return iron; }
    bool hasResources(int f, int w, int s, int i) { return food >= f && wood >= w && stone >= s && iron >= i; }
    ~Resources();
};

// ============================== Economy Class ==============================
class Economy {
private:
    float income;
    float expenditure;
    float taxRate;
public:
    Economy();
    void collectTaxes(int population);
    void updateExpenditure(float amount);
    void audit();
    void displayEconomy();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Economy();
};

// ============================== Event Class ==============================
class Event {
public:
    Event();
    void randomEvent(Player* players, int numPlayers, Diplomacy* diplomacy, Market* market);
    ~Event();
};

// ============================== Communication Class ==============================
class Communication {
private:
    static const int MAX_MESSAGES = 10;
    Message messages[MAX_MESSAGES];
    int messageCount;
public:
    Communication();
    void sendMessage(int senderId, int recipientId, string content);
    void viewMessages(int playerId);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Communication();
};

// ============================== Diplomacy Class ==============================
class Diplomacy {
private:
    static const int MAX_TREATIES = 10;
    Treaty treaties[MAX_TREATIES];
    int treatyCount;
public:
    Diplomacy();
    void proposeTreaty(int player1Id, int player2Id, string type, int duration);
    void breakTreaty(int player1Id, int player2Id);
    bool hasAlliance(int player1Id, int player2Id);
    void updateTreaties();
    void displayTreaties(int playerId);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Diplomacy();
};

// ============================== Market Class ==============================
class Market {
private:
    static const int MAX_OFFERS = 10;
    TradeOffer offers[MAX_OFFERS];
    int offerCount;
public:
    Market();
    void proposeTrade(int senderId, int recipientId, int offerF, int offerW, int offerS, int offerI,
        int requestF, int requestW, int requestS, int requestI, bool smuggling);
    void acceptTrade(int offerIndex, Player* players, Diplomacy* diplomacy);
    void viewOffers(int playerId);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Market();
};

// ============================== Conflict Class ==============================
class Conflict {
public:
    Conflict();
    void declareWar(int attackerId, int defenderId, Player* players, Diplomacy* diplomacy, Map* map);
    void resolveBattle(int attackerId, int defenderId, Player* players, Map* map);
    ~Conflict();
};

// ============================== Map Class ==============================
class Map {
private:
    static const int MAP_SIZE = 5; // 5x5 grid
    int grid[MAP_SIZE][MAP_SIZE]; // Player ID or -1 for neutral
    struct Position {
        int x, y;
    };
    Position playerPositions[4]; // Max 4 players
public:
    Map();
    void initialize(Player* players, int numPlayers);
    void movePlayer(int playerId, int newX, int newY);
    void captureTerritory(int playerId, int x, int y);
    void displayMap(int playerId);
    bool areAdjacent(int player1Id, int player2Id);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
    ~Map();
};

// ============================== Game Class ==============================
class Game {
private:
    static const int MAX_PLAYERS = 4;
    Player players[MAX_PLAYERS];
    int numPlayers;
    Communication* communication;
    Diplomacy* diplomacy;
    Market* market;
    Conflict* conflict;
    Map* map;
    Event* event;
    int currentTurn;
    bool endGame;
public:
    Game();
    void initialize();
    void playTurn(int playerId);
    void saveGame();
    void loadGame();
    Player* getPlayers() { return players; }
    int getNumPlayers() { return numPlayers; }
    Diplomacy* getDiplomacy() { return diplomacy; }
    Market* getMarket() { return market; }
    Event* getEvent() { return event; }
    bool isGameEnded() { return endGame; }
    ~Game();
};
#endif