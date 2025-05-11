#include "Stronghold.h"

using namespace std;

Society::Society() {
    peasants = 100;
    merchants = 50;
    nobles = 10;
}

void Society::displaySociety() {
    cout << "Society Stats: \n";
    cout << "Peasants: " << peasants << "\n";
    cout << "Merchants: " << merchants << "\n";
    cout << "Nobles: " << nobles << "\n";
}

void Society::manageConflict() {
    if (peasants > 120) {
        cout << "Revolt in society! Peasants demand more rights.\n";
    }
    else if (nobles > 15) {
        cout << "Noble class is growing, increasing tensions.\n";
    }
}

void Society::adjustClass(int p, int m, int n) {
    peasants += p;
    merchants += m;
    nobles += n;
    peasants = max(0, peasants);
    merchants = max(0, merchants);
    nobles = max(0, nobles);
}

void Society::saveToFile(ofstream& out) {
    out << "# Society\n";
    out << "Peasants: " << peasants << "\n";
    out << "Merchants: " << merchants << "\n";
    out << "Nobles: " << nobles << "\n";
}

void Society::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    // Check if old format (raw values)
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Peasants:") != 0) {
        oldFormat = true;
        in >> peasants >> merchants >> nobles;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Peasants:") == 0) {
                in >> peasants;
                in.ignore();
            }
            else if (line.find("Merchants:") == 0) {
                in >> merchants;
                in.ignore();
            }
            else if (line.find("Nobles:") == 0) {
                in >> nobles;
                in.ignore();
                break;
            }
        }
    }
    peasants = max(0, peasants);
    merchants = max(0, merchants);
    nobles = max(0, nobles);
}

Society::~Society() {
    cout << "Society destroyed.\n";
}