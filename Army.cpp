#include "Stronghold.h"

using namespace std;

Army::Army() {
    soldiers = 100;
    trained = 0;
    morale = 100;
    food = 200;
}

void Army::recruit(int people, Population* pop) {
    if (people < 0) {
        cout << "Cannot recruit negative people." << endl;
        return;
    }
    if (pop->getTotal() >= people) {
        soldiers += people;
        pop->setTotal(pop->getTotal() - people);
        cout << people << " soldiers recruited." << endl;
    }
    else {
        cout << "Not enough population to recruit."<<endl;
    }
}

void Army::train() {
    if (food >= 50) {
        trained += 10;
        food -= 50;
        cout << "Training 10 soldiers. " << food << " food remaining.\n";
    }
    else {
        cout << "Not enough food to train soldiers.\n";
    }
}

void Army::feed(int rations) {
    if (rations >= 0 && rations <= food) {
        food -= rations;
        cout << "Fed " << rations << " rations to the army.\n";
    }
    else {
        cout << "Invalid or insufficient food to feed soldiers.\n";
    }
}

void Army::displayArmy() {
    cout << "Army Size: " << soldiers << "\n";
    cout << "Trained Soldiers: " << trained << "\n";
    cout << "Morale: " << morale << "\n";
    cout << "Food: " << food << "\n";
}

void Army::saveToFile(ofstream& out) {
    out << "# Army\n";
    out << "Soldiers: " << soldiers << "\n";
    out << "Trained: " << trained << "\n";
    out << "Morale: " << morale << "\n";
    out << "Food: " << food << "\n";
}

void Army::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Soldiers:") != 0) {
        oldFormat = true;
        in >> soldiers >> trained >> morale >> food;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Soldiers:") == 0) {
                in >> soldiers;
                in.ignore();
            }
            else if (line.find("Trained:") == 0) {
                in >> trained;
                in.ignore();
            }
            else if (line.find("Morale:") == 0) {
                in >> morale;
                in.ignore();
            }
            else if (line.find("Food:") == 0) {
                in >> food;
                in.ignore();
                break;
            }
        }
    }
    soldiers = max(0, soldiers);
    trained = max(0, trained);
    morale = max(0, morale);
    food = max(0, food);
}

Army::~Army() {
    cout << "Army destroyed.\n";
}