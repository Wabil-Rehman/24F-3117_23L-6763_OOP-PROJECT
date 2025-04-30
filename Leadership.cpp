#include "Stronghold.h"

// Constructor
Leadership::Leadership() {
    currentLeader = "King";
    policy = "Peace";
    approval = 100;
}

// Elect a new leader
void Leadership::electNewLeader(string name) {
    currentLeader = name;
    cout << "New leader elected: " << currentLeader << "\n";
}

// Change the leadership policy
void Leadership::changePolicy(string newPolicy) {
    policy = newPolicy;
    cout << "New policy: " << policy << "\n";
}

// Display leadership details
void Leadership::displayLeadership() {
    cout << "Current Leader: " << currentLeader << "\n";
    cout << "Policy: " << policy << "\n";
    cout << "Approval: " << approval << "\n";
}

// Save leadership data to file
void Leadership::saveToFile(ofstream& out) {
    out << currentLeader << "\n";
    out << policy << "\n";
    out << approval << "\n";
}

// Load leadership data from file
void Leadership::loadFromFile(ifstream& in) {
    getline(in, currentLeader);
    getline(in, policy);
    in >> approval;
    in.ignore(); // Clear newline after reading integer
}

// Destructor
Leadership::~Leadership() {
    cout << "Leadership system destroyed.\n";
}
