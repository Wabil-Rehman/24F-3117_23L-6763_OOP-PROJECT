#include "Stronghold.h"

using namespace std;

Resources::Resources() {
    food = 1000;
    wood = 500;
    stone = 300;
    iron = 200;
}

void Resources::gatherResources(int f, int w, int s, int i) {
    if (f >= 0 && w >= 0 && s >= 0 && i >= 0) {
        food += f;
        wood += w;
        stone += s;
        iron += i;
        cout << "Resources gathered: Food: " << f << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
    }
    else {
        cout << "Invalid resource amounts.\n";
    }
}

void Resources::consumeResources(int f, int w, int s, int i) {
    if (f >= 0 && w >= 0 && s >= 0 && i >= 0 && food >= f && wood >= w && stone >= s && iron >= i) {
        food -= f;
        wood -= w;
        stone -= s;
        iron -= i;
        cout << "Resources consumed: Food: " << f << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
    }
    else {
        cout << "Invalid or insufficient resources.\n";
    }
}

void Resources::displayResources() {
    cout << "Food: " << food << "\n";
    cout << "Wood: " << wood << "\n";
    cout << "Stone: " << stone << "\n";
    cout << "Iron: " << iron << "\n";
}

void Resources::saveToFile(ofstream& out) {
    out << "# Resources\n";
    out << "Food: " << food << "\n";
    out << "Wood: " << wood << "\n";
    out << "Stone: " << stone << "\n";
    out << "Iron: " << iron << "\n";
}

void Resources::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Food:") != 0) {
        oldFormat = true;
        in >> food >> wood >> stone >> iron;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Food:") == 0) {
                in >> food;
                in.ignore();
            }
            else if (line.find("Wood:") == 0) {
                in >> wood;
                in.ignore();
            }
            else if (line.find("Stone:") == 0) {
                in >> stone;
                in.ignore();
            }
            else if (line.find("Iron:") == 0) {
                in >> iron;
                in.ignore();
                break;
            }
        }
    }
    food = max(0, food);
    wood = max(0, wood);
    stone = max(0, stone);
    iron = max(0, iron);
}

Resources::~Resources() {
    cout << "Resources destroyed.\n";
}