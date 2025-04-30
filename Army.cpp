#include "Stronghold.h"

// Constructor
Army::Army() {
    soldiers = 100;
    trained = 0;
    morale = 100;
    food = 200;
}

// Recruit soldiers into the army
void Army::recruit(int people) {
    soldiers += people;
    cout << people << " soldiers recruited.\n";
}

// Train soldiers to improve their skills
void Army::train() {
    if (food > 50) {
        trained += 10;
        food -= 50;
        cout << "Training 10 soldiers. " << food << " food remaining.\n";
    }
    else {
        cout << "Not enough food to train soldiers.\n";
    }
}

// Feed soldiers
void Army::feed(int rations) {
    food -= rations;
    cout << "Fed " << rations << " rations to the army.\n";
}

// Display army details
void Army::displayArmy() {
    cout << "Army Size: " << soldiers << "\n";
    cout << "Trained Soldiers: " << trained << "\n";
    cout << "Morale: " << morale << "\n";
    cout << "Food: " << food << "\n";
}

// Save army state to file
void Army::saveToFile(ofstream& out) {
    out << soldiers << " " << trained << " " << morale << " " << food << "\n";
}

// Load army state from file
void Army::loadFromFile(ifstream& in) {
    in >> soldiers >> trained >> morale >> food;
}

// Destructor
Army::~Army() {
    cout << "Army destroyed.\n";
}
