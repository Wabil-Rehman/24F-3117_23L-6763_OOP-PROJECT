#include "Stronghold.h"

using namespace std;

Population::Population() {
    total = 200;
    sick = 0;
    rebels = 0;
}

void Population::updatePopulation(int foodSupply, int shelter, bool war) {
    if (foodSupply >= 0 && foodSupply <= 100 && shelter >= 0 && shelter <= 100) {
        if (foodSupply < 50) {
            sick += 10;
        }
        if (war) {
            total -= 20;
        }
        if (sick > 10) {
            rebels += 5;
        }
        total -= sick;
        total = max(0, total);
        sick = max(0, sick);
        rebels = max(0, rebels);
    }
    else {
        cout << "Invalid food supply or shelter value.\n";
    }
}

void Population::displayPopulation() {
    cout << "Total Population: " << total << "\n";
    cout << "Sick Population: " << sick << "\n";
    cout << "Rebels: " << rebels << "\n";
}

void Population::saveToFile(ofstream& out) {
    out << "# Population\n";
    out << "Total: " << total << "\n";
    out << "Sick: " << sick << "\n";
    out << "Rebels: " << rebels << "\n";
}

void Population::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Total:") != 0) {
        oldFormat = true;
        in >> total >> sick >> rebels;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Total:") == 0) {
                in >> total;
                in.ignore();
            }
            else if (line.find("Sick:") == 0) {
                in >> sick;
                in.ignore();
            }
            else if (line.find("Rebels:") == 0) {
                in >> rebels;
                in.ignore();
                break;
            }
        }
    }
    total = max(0, total);
    sick = max(0, sick);
    rebels = max(0, rebels);
}

Population::~Population() {
    cout << "Population destroyed.\n";
}