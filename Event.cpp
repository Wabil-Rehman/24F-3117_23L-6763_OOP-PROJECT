#include "Stronghold.h"
#include <ctime>
#include <cstdlib>

// Constructor
Event::Event() {
    srand(static_cast<unsigned int>(time(0)));  // Random seed
}

// Trigger a random event that can impact the kingdom
void Event::randomEvent(Population* pop, Army* army, Resources* res, Bank* bank, Leadership* leader) {
    int eventChoice = rand() % 4;  // Random number between 0-3 for different events

    switch (eventChoice) {
    case 0:
        cout << "A famine has struck! Food is scarce.\n";
        res->consumeResources(200, 0, 0, 0);
        break;
    case 1:
        cout << "War has broken out! Mobilizing the army.\n";
        army->recruit(50);
        break;
    case 2:
        cout << "A rebellion is brewing in the kingdom.\n";
        pop->updatePopulation(0, 0, true);
        break;
    case 3:
        cout << "A drought has occurred, affecting resources.\n";
        res->consumeResources(100, 0, 0, 0);
        break;
    default:
        cout << "No event occurred.\n";
    }
}

// Destructor
Event::~Event() {
    cout << "Event system destroyed.\n";
}
