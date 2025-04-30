#include "Stronghold.h"

// Constructor
Population::Population() {
    total = 200;
    sick = 0;
    rebels = 0;
}

// Update the population based on various factors
void Population::updatePopulation(int foodSupply, int shelter, bool war) {
    if (foodSupply < 50) {
        sick += 10;
    }
    if (war) {
        total -= 20; // Loss due to war
    }
    if (sick > 10) {
        rebels += 5; // Increased chances of revolt
    }
    total -= sick; // Sick population doesn't contribute
}

// Display population details
void Population::displayPopulation() {
    cout << "Total Population: " << total << "\n";
    cout << "Sick Population: " << sick << "\n";
    cout << "Rebels: " << rebels << "\n";
}

// Save population data to file
void Population::saveToFile(ofstream& out) {
    out << total << "\n";
    out << sick << "\n";
    out << rebels << "\n";
}

// Load population data from file
void Population::loadFromFile(ifstream& in) {
    in >> total;
    in >> sick;
    in >> rebels;
    in.ignore(); // Clear newline after reading integers
}

// Destructor
Population::~Population() {
    cout << "Population destroyed.\n";
}
