#include "Stronghold.h"

// Constructor
Society::Society() {
    peasants = 100;
    merchants = 50;
    nobles = 10;
}

// Display society information
void Society::displaySociety() {
    cout << "Society Stats: \n";
    cout << "Peasants: " << peasants << "\n";
    cout << "Merchants: " << merchants << "\n";
    cout << "Nobles: " << nobles << "\n";
}

// Manage conflict between classes
void Society::manageConflict() {
    // Simulate some societal conflict logic here
    if (peasants > 120) {
        cout << "Revolt in society! Peasants demand more rights.\n";
    }
    else if (nobles > 15) {
        cout << "Noble class is growing, increasing tensions.\n";
    }
}

// Adjust social class populations
void Society::adjustClass(int p, int m, int n) {
    peasants += p;
    merchants += m;
    nobles += n;
}

// Save society data to file
void Society::saveToFile(ofstream& out) {
    out << peasants << "\n";
    out << merchants << "\n";
    out << nobles << "\n";
}

// Load society data from file
void Society::loadFromFile(ifstream& in) {
    in >> peasants;
    in >> merchants;
    in >> nobles;
    in.ignore(); // clear newline
}

// Destructor
Society::~Society() {
    cout << "Society destroyed.\n";
}
