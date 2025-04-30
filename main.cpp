#include "Stronghold.h"
#include <fstream>

void showBanner() {
    cout << "\n==============================================\n";
    cout << "        WELCOME TO THE STRONGHOLD ENGINE       \n";
    cout << "==============================================\n";
}

void menu() {
    cout << "\n------------ Main Menu ------------\n";
    cout << "1. View Society\n";
    cout << "2. Update Population\n";
    cout << "3. Manage Army\n";
    cout << "4. Change Leadership\n";
    cout << "5. Manage Bank\n";
    cout << "6. Manage Resources\n";
    cout << "7. Manage Economy\n";
    cout << "8. Trigger Random Event\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

void saveGame(Society* society, Population* population, Army* army, Leadership* leader,
    Bank* bank, Resources* resources, Economy* economy) {

    ofstream outFile("save_game.txt");

    if (outFile.is_open()) {
        society->saveToFile(outFile);
        population->saveToFile(outFile);
        army->saveToFile(outFile);
        leader->saveToFile(outFile);
        bank->saveToFile(outFile);
        resources->saveToFile(outFile);
        economy->saveToFile(outFile);

        cout << "Game saved successfully.\n";
    }
    else {
        cout << "Error saving game.\n";
    }

    outFile.close();
}

void loadGame(Society* society, Population* population, Army* army, Leadership* leader,
    Bank* bank, Resources* resources, Economy* economy) {

    ifstream inFile("save_game.txt");

    if (inFile.is_open()) {
        society->loadFromFile(inFile);
        population->loadFromFile(inFile);
        army->loadFromFile(inFile);
        leader->loadFromFile(inFile);
        bank->loadFromFile(inFile);
        resources->loadFromFile(inFile);
        economy->loadFromFile(inFile);

        cout << "Game loaded successfully.\n";
    }
    else {
        cout << "No save file found, starting a new game.\n";
    }

    inFile.close();
}

int main() {
    // Dynamically allocate memory for all components
    Society* society = new Society();
    Population* population = new Population();
    Army* army = new Army();
    Leadership* leader = new Leadership();
    Bank* bank = new Bank();
    Resources* resources = new Resources();
    Economy* economy = new Economy();
    Event* event = new Event();

    int choice;
    showBanner();

    // Attempt to load previous game data
    loadGame(society, population, army, leader, bank, resources, economy);

    do {
        menu();
        cin >> choice;
        switch (choice) {
        case 1:
            society->displaySociety();
            break;
        case 2: {
            int food, shelter;
            bool war;
            cout << "Enter food supply (0-100): "; cin >> food;
            cout << "Enter shelter level (0-100): "; cin >> shelter;
            cout << "Is there war? (1-Yes / 0-No): "; cin >> war;
            population->updatePopulation(food, shelter, war);
            population->displayPopulation();
            break;
        }
        case 3:
            army->train();
            army->feed(50);
            army->displayArmy();
            break;
        case 4: {
            string name, policy;
            cout << "Enter new leader name: "; cin >> name;
            cout << "Enter policy direction (e.g. Peace/War): "; cin >> policy;
            leader->electNewLeader(name);
            leader->changePolicy(policy);
            leader->displayLeadership();
            break;
        }
        case 5:
            bank->audit();
            bank->takeLoan(1000);
            bank->repayLoan(500);
            bank->displayBank();
            break;
        case 6:
            resources->gatherResources(100, 80, 60, 40);
            resources->consumeResources(50, 30, 20, 10);
            resources->displayResources();
            break;
        case 7: {
            economy->collectTaxes(200);
            economy->updateExpenditure(200);
            economy->audit();
            economy->displayEconomy();
            break;
        }
        case 8:
            event->randomEvent(population, army, resources, bank, leader);
            break;
        case 9:
            cout << "\nExiting Stronghold Engine. Long live the Kingdom!\n";
            saveGame(society, population, army, leader, bank, resources, economy); // Save game on exit
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 9);

    // Clean up dynamically allocated memory
    delete society;
    delete population;
    delete army;
    delete leader;
    delete bank;
    delete resources;
    delete economy;
    delete event;

    return 0;
}
