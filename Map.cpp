#include "Stronghold.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Map::Map() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            grid[i][j] = -1;
        }
    }
    for (int i = 0; i < 4; i++) {
        playerPositions[i].x = -1;
        playerPositions[i].y = -1;
    }
}

void Map::initialize(Player* players, int numPlayers) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < numPlayers; i++) {
        int x, y;
        bool validPosition = false;
        do {
            x = rand() % MAP_SIZE;
            y = rand() % MAP_SIZE;
            if (grid[x][y] == -1) {
                validPosition = true;
                grid[x][y] = i;
                playerPositions[i].x = x;
                playerPositions[i].y = y;
            }
        } while (!validPosition);
    }
}

void Map::movePlayer(int playerId, int newX, int newY) {
    if (playerId < 0 || playerId >= 4 || newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE) {
        cout << "Invalid move: out of bounds or invalid player ID.\n";
        return;
    }
    int oldX = playerPositions[playerId].x;
    int oldY = playerPositions[playerId].y;
    if (oldX == -1 || oldY == -1) {
        cout << "Player has no valid position on map.\n";
        return;
    }
    if (abs(newX - oldX) + abs(newY - oldY) > 1) {
        cout << "Invalid move: can only move one step.\n";
        return;
    }
    if (grid[newX][newY] != -1) {
        cout << "Cannot move: position occupied.\n";
        return;
    }
    grid[oldX][oldY] = -1;
    grid[newX][newY] = playerId;
    playerPositions[playerId].x = newX;
    playerPositions[playerId].y = newY;
    cout << "Player " << playerId << " moved to (" << newX << ", " << newY << ").\n";
}

void Map::captureTerritory(int playerId, int x, int y) {
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
        if (grid[x][y] != playerId) {
            grid[x][y] = playerId;
            cout << "Player " << playerId << " captured territory at (" << x << ", " << y << ").\n";
        }
        else {
            cout << "Territory at (" << x << ", " << y << ") already owned by Player " << playerId << ".\n";
        }
    }
    else {
        cout << "Invalid coordinates for capturing territory.\n";
    }
}

void Map::displayMap(int playerId) {
    cout << "Map (Player " << playerId << " perspective):\n";
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (grid[i][j] == -1) {
                cout << " . ";
            }
            else if (grid[i][j] == playerId) {
                cout << " P ";
            }
            else {
                cout << " " << grid[i][j] << " ";
            }
        }
        cout << "\n";
    }
    cout << "Player " << playerId << " position: (" << playerPositions[playerId].x << ", " << playerPositions[playerId].y << ")\n";
}

bool Map::areAdjacent(int player1Id, int player2Id) {
    if (player1Id < 0 || player1Id >= 4 || player2Id < 0 || player2Id >= 4) {
        return false;
    }
    int x1 = playerPositions[player1Id].x;
    int y1 = playerPositions[player1Id].y;
    int x2 = playerPositions[player2Id].x;
    int y2 = playerPositions[player2Id].y;
    if (x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1) {
        return false;
    }
    return abs(x1 - x2) + abs(y1 - y2) == 1;
}

void Map::saveToFile(ofstream& outFile) {
    outFile << "# Map\n";
    outFile << "Grid: ";
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            outFile << grid[i][j] << " ";
        }
    }
    outFile << "\n";
    for (int i = 0; i < 4; i++) {
        outFile << "Player" << i << "_X: " << playerPositions[i].x << "\n";
        outFile << "Player" << i << "_Y: " << playerPositions[i].y << "\n";
    }
    outFile << "\n";
}

void Map::loadFromFile(ifstream& inFile) {
    string line;
    bool oldFormat = false;
    streampos startPos = inFile.tellg();
    getline(inFile, line);
    inFile.seekg(startPos);
    if (line.find("Grid:") != 0) {
        oldFormat = true;
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                inFile >> grid[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            inFile >> playerPositions[i].x >> playerPositions[i].y;
        }
        inFile.ignore();
    }
    else {
        while (getline(inFile, line)) {
            if (line.find("Grid:") == 0) {
                for (int i = 0; i < MAP_SIZE; i++) {
                    for (int j = 0; j < MAP_SIZE; j++) {
                        inFile >> grid[i][j];
                    }
                }
                inFile.ignore();
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            while (getline(inFile, line)) {
                if (line.find("Player" + to_string(i) + "_X:") == 0) {
                    inFile >> playerPositions[i].x;
                    inFile.ignore();
                }
                else if (line.find("Player" + to_string(i) + "_Y:") == 0) {
                    inFile >> playerPositions[i].y;
                    inFile.ignore();
                    break;
                }
            }
        }
    }
}

Map::~Map() {
    cout << "Map destroyed.\n";
}