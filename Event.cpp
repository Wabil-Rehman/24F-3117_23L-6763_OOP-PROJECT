#include "Stronghold.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Event::Event() {
    srand(static_cast<unsigned int>(time(0)));
}

void Event::randomEvent(Player* players, int numPlayers, Diplomacy* diplomacy, Market* market) {
    int eventChoice = rand() % 6;
    int playerId = rand() % numPlayers;
    switch (eventChoice) {
    case 0:
        cout << "A famine has struck Player " << playerId << "!\n";
        players[playerId].resources->consumeResources(200, 0, 0, 0);
        break;
    case 1:
        cout << "War has broken out! Player " << playerId << " recruits soldiers.\n";
        players[playerId].army->recruit(50, players[playerId].population);
        break;
    case 2:
        cout << "A rebellion is brewing in Player " << playerId << "'s kingdom.\n";
        players[playerId].population->updatePopulation(0, 0, true);
        break;
    case 3:
        cout << "A drought has affected Player " << playerId << "'s resources.\n";
        players[playerId].resources->consumeResources(100, 0, 0, 0);
        break;
    case 4:
        cout << "Trade dispute! Player " << playerId << "'s trade is canceled.\n";
        market->viewOffers(playerId);
        break;
    case 5:
        cout << "Diplomatic crisis! Player " << playerId << "'s treaty is broken.\n";
        int otherPlayerId = (playerId + 1) % numPlayers;
        diplomacy->breakTreaty(playerId, otherPlayerId);
        break;
    }
}

Event::~Event() {
    cout << "Event system destroyed.\n";
}