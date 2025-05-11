#include "Stronghold.h"

using namespace std;

Leadership::Leadership() {
    currentLeader = "King";
    policy = "Peace";
    approval = 100;
}

void Leadership::electNewLeader(string name) {
    if (!name.empty()) {
        currentLeader = name;
        cout << "New leader elected: " << currentLeader << "\n";
    }
    else {
        cout << "Invalid leader name.\n";
    }
}

void Leadership::changePolicy(string newPolicy) {
    if (!newPolicy.empty()) {
        policy = newPolicy;
        cout << "New policy: " << policy << "\n";
    }
    else {
        cout << "Invalid policy.\n";
    }
}

void Leadership::displayLeadership() {
    cout << "Current Leader: " << currentLeader << "\n";
    cout << "Policy: " << policy << "\n";
    cout << "Approval: " << approval << "\n";
}

void Leadership::saveToFile(ofstream& out) {
    out << "# Leadership\n";
    out << "Leader: " << currentLeader << "\n";
    out << "Policy: " << policy << "\n";
    out << "Approval: " << approval << "\n";
}

void Leadership::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Leader:") != 0) {
        oldFormat = true;
        getline(in, currentLeader);
        getline(in, policy);
        in >> approval;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Leader:") == 0) {
                getline(in, currentLeader);
            }
            else if (line.find("Policy:") == 0) {
                getline(in, policy);
            }
            else if (line.find("Approval:") == 0) {
                in >> approval;
                in.ignore();
                break;
            }
        }
    }
    approval = max(0, approval);
}

Leadership::~Leadership() {
    cout << "Leadership system destroyed.\n";
}