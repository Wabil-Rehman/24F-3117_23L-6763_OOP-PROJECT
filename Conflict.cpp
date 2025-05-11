#include "Stronghold.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Conflict::Conflict() {
    srand(static_cast<unsigned int>(time(0)));
}

void Conflict::declareWar(int attackerId, int defenderId, Player* players, Diplomacy* diplomacy, Map* map) {
    if (attackerId == defenderId) {
        cout << "Cannot declare war on self.\n";
        return;
    }
    if (diplomacy->hasAlliance(attackerId, defenderId)) {
        cout << "Betrayal! Attacking an ally.\n";
        players[attackerId].leadership->reduceApproval(20);
        players[attackerId].army->reduceMorale(15);
        diplomacy->breakTreaty(attackerId, defenderId);
    }
    if (map->areAdjacent(attackerId, defenderId)) {
        cout << "War declared! Battle begins.\n";
        resolveBattle(attackerId, defenderId, players, map);
    }
    else {
        cout << "Cannot attack: Players are not adjacent on the map.\n";
    }
}

void Conflict::resolveBattle(int attackerId, int defenderId, Player* players, Map* map) {
    Army* attackerArmy = players[attackerId].army;
    Army* defenderArmy = players[defenderId].army;
    int attackerStrength = attackerArmy->getSoldiers() + attackerArmy->getTrained() * 2;
    int defenderStrength = defenderArmy->getSoldiers() + defenderArmy->getTrained() * 2;

    attackerStrength = attackerStrength * attackerArmy->getMorale() / 100;
    defenderStrength = defenderStrength * defenderArmy->getMorale() / 100;

    int result = (rand() % 100) + attackerStrength - defenderStrength;
    if (result > 50) {
        cout << "Player " << attackerId << " wins the battle!\n";
        defenderArmy->reduceSoldiers(defenderArmy->getSoldiers() / 2);
        attackerArmy->reduceSoldiers(attackerArmy->getSoldiers() / 4);
        players[defenderId].resources->consumeResources(100, 50, 50, 20);
        map->captureTerritory(attackerId, rand() % 5, rand() % 5);
    }
    else if (result < -50) {
        cout << "Player " << defenderId << " wins the battle!\n";
        attackerArmy->reduceSoldiers(attackerArmy->getSoldiers() / 2);
        defenderArmy->reduceSoldiers(defenderArmy->getSoldiers() / 4);
        players[attackerId].resources->consumeResources(100, 50, 50, 20);
    }
    else {
        cout << "Battle is a draw.\n";
        attackerArmy->reduceSoldiers(attackerArmy->getSoldiers() / 3);
        defenderArmy->reduceSoldiers(defenderArmy->getSoldiers() / 3);
    }
}

Conflict::~Conflict() {
    cout << "Conflict system destroyed.\n";
}