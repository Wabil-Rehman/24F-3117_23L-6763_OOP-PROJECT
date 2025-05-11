#include "Stronghold.h"

using namespace std;

void showBanner() {
    cout << "\n==============================================\n";
    cout << "        WELCOME TO THE STRONGHOLD ENGINE       \n";
    cout << "==============================================\n";
}

int main() {
    Game* game = new Game();
    showBanner();
    game->loadGame();
    while (!game->isGameEnded()) { // Check if game should end
        for (int i = 0; i < game->getNumPlayers(); i++) {
            game->playTurn(i);
            if (game->isGameEnded()) { // Check after each turn
                break;
            }
            game->getDiplomacy()->updateTreaties();
            game->getEvent()->randomEvent(game->getPlayers(), game->getNumPlayers(),
                game->getDiplomacy(), game->getMarket());
        }
    }
    cout << "Game ended. Final state saved.\n";
    delete game;
    return 0;
}