#include "Stronghold.h"

// Constructor
Resources::Resources() {
    food = 1000;
    wood = 500;
    stone = 300;
    iron = 200;
}

// Gather resources
void Resources::gatherResources(int f, int w, int s, int i) {
    food += f;
    wood += w;
    stone += s;
    iron += i;
    cout << "Resources gathered: Food: " << f << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
}

// Consume resources
void Resources::consumeResources(int f, int w, int s, int i) {
    food -= f;
    wood -= w;
    stone -= s;
    iron -= i;
    cout << "Resources consumed: Food: " << f << ", Wood: " << w << ", Stone: " << s << ", Iron: " << i << "\n";
}

// Display resource details
void Resources::displayResources() {
    cout << "Food: " << food << "\n";
    cout << "Wood: " << wood << "\n";
    cout << "Stone: " << stone << "\n";
    cout << "Iron: " << iron << "\n";
}

// Save resource data to file
void Resources::saveToFile(ofstream& out) {
    out << food << "\n";
    out << wood << "\n";
    out << stone << "\n";
    out << iron << "\n";
}

// Load resource data from file
void Resources::loadFromFile(ifstream& in) {
    in >> food;
    in >> wood;
    in >> stone;
    in >> iron;
    in.ignore(); // clear newline
}

// Destructor
Resources::~Resources() {
    cout << "Resources destroyed.\n";
}
