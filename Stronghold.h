#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
    void recruit(int people);
    void train();
    void feed(int rations);
    void displayArmy();
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
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
    void randomEvent(Population* pop, Army* army, Resources* res, Bank* bank, Leadership* leader);
    ~Event();
};

#endif
