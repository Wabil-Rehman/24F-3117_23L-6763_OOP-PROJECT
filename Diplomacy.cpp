#include "Stronghold.h"

using namespace std;

Treaty::Treaty() : player1Id(-1), player2Id(-1), type(""), duration(0), active(false) {}

Diplomacy::Diplomacy() : treatyCount(0) {
    for (int i = 0; i < MAX_TREATIES; i++) {
        treaties[i] = Treaty();
    }
}

void Diplomacy::proposeTreaty(int player1Id, int player2Id, string type, int duration) {
    if (treatyCount < MAX_TREATIES && player1Id != player2Id && duration > 0 &&
        (type == "Alliance" || type == "Non-Aggression" || type == "Trade")) {
        treaties[treatyCount].player1Id = player1Id;
        treaties[treatyCount].player2Id = player2Id;
        treaties[treatyCount].type = type;
        treaties[treatyCount].duration = duration;
        treaties[treatyCount].active = true;
        treatyCount++;
        cout << "Treaty proposed: " << type << " between Player " << player1Id << " and Player " << player2Id << ".\n";
    }
    else {
        cout << "Cannot propose treaty: invalid parameters or treaty limit reached.\n";
    }
}

void Diplomacy::breakTreaty(int player1Id, int player2Id) {
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active &&
            ((treaties[i].player1Id == player1Id && treaties[i].player2Id == player2Id) ||
                (treaties[i].player1Id == player2Id && treaties[i].player2Id == player1Id))) {
            treaties[i].active = false;
            cout << "Treaty broken between Player " << player1Id << " and Player " << player2Id << ".\n";
            return;
        }
    }
    cout << "No treaty found.\n";
}

bool Diplomacy::hasAlliance(int player1Id, int player2Id) {
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active &&
            ((treaties[i].player1Id == player1Id && treaties[i].player2Id == player2Id) ||
                (treaties[i].player1Id == player2Id && treaties[i].player2Id == player1Id)) &&
            treaties[i].type == "Alliance") {
            return true;
        }
    }
    return false;
}

void Diplomacy::updateTreaties() {
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active) {
            treaties[i].duration--;
            if (treaties[i].duration <= 0) {
                treaties[i].active = false;
                cout << "Treaty expired between Player " << treaties[i].player1Id << " and Player " << treaties[i].player2Id << ".\n";
            }
        }
    }
}
void Diplomacy::displayTreaties(int playerId) {
    cout << "Treaties for Player " << playerId << ":\n";
    bool hasTreaties = false;
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active &&
            (treaties[i].player1Id == playerId || treaties[i].player2Id == playerId)) {
            cout << treaties[i].type << " with Player "
                << (treaties[i].player1Id == playerId ? treaties[i].player2Id : treaties[i].player1Id)
                << ", Duration: " << treaties[i].duration << " turns\n";
            hasTreaties = true;
        }
    }
    if (!hasTreaties) {
        cout << "No treaties.\n";
    }
}

void Diplomacy::saveToFile(ofstream& outFile) {
    outFile << "# Diplomacy\n";
    outFile << "TreatyCount: " << treatyCount << "\n";
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active) {
            outFile << "Treaty" << i << "_Player1: " << treaties[i].player1Id << "\n";
            outFile << "Treaty" << i << "_Player2: " << treaties[i].player2Id << "\n";
            outFile << "Treaty" << i << "_Type: " << treaties[i].type << "\n";
            outFile << "Treaty" << i << "_Duration: " << treaties[i].duration << "\n";
        }
    }
    outFile << "\n";
}

void Diplomacy::loadFromFile(ifstream& inFile) {
    string line;
    bool oldFormat = false;
    streampos startPos = inFile.tellg();
    getline(inFile, line);
    inFile.seekg(startPos);
    if (line.find("TreatyCount:") != 0) {
        oldFormat = true;
        inFile >> treatyCount;
        inFile.ignore();
        for (int i = 0; i < treatyCount; i++) {
            inFile >> treaties[i].player1Id >> treaties[i].player2Id;
            inFile >> treaties[i].type;
            inFile >> treaties[i].duration;
            treaties[i].active = true;
            inFile.ignore();
        }
    }
    else {
        while (getline(inFile, line)) {
            if (line.find("TreatyCount:") == 0) {
                inFile >> treatyCount;
                inFile.ignore();
                break;
            }
        }
        for (int i = 0; i < treatyCount; i++) {
            while (getline(inFile, line)) {
                if (line.find("Treaty" + to_string(i) + "_Player1:") == 0) {
                    inFile >> treaties[i].player1Id;
                    inFile.ignore();
                }
                else if (line.find("Treaty" + to_string(i) + "_Player2:") == 0) {
                    inFile >> treaties[i].player2Id;
                    inFile.ignore();
                }
                else if (line.find("Treaty" + to_string(i) + "_Type:") == 0) {
                    inFile >> treaties[i].type;
                    inFile.ignore();
                }
                else if (line.find("Treaty" + to_string(i) + "_Duration:") == 0) {
                    inFile >> treaties[i].duration;
                    treaties[i].active = true;
                    inFile.ignore();
                    break;
                }
            }
        }
    }
}

Diplomacy::~Diplomacy() {
    cout << "Diplomacy system destroyed.\n";
}