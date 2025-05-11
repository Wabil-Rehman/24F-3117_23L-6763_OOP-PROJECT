#include "Stronghold.h"
#include <cstdlib>
#include <ctime>

using namespace std;

TradeOffer::TradeOffer() : senderId(-1), recipientId(-1), offerFood(0), offerWood(0), offerStone(0), offerIron(0),
requestFood(0), requestWood(0), requestStone(0), requestIron(0), smuggling(false), active(false) {
}

Market::Market() : offerCount(0) {
    for (int i = 0; i < MAX_OFFERS; i++) {
        offers[i] = TradeOffer();
    }
    srand(static_cast<unsigned int>(time(0)));
}

void Market::proposeTrade(int senderId, int recipientId, int offerF, int offerW, int offerS, int offerI,
    int requestF, int requestW, int requestS, int requestI, bool smuggling) {
    if (offerCount < MAX_OFFERS && senderId != recipientId &&
        offerF >= 0 && offerW >= 0 && offerS >= 0 && offerI >= 0 &&
        requestF >= 0 && requestW >= 0 && requestS >= 0 && requestI >= 0) {
        offers[offerCount].senderId = senderId;
        offers[offerCount].recipientId = recipientId;
        offers[offerCount].offerFood = offerF;
        offers[offerCount].offerWood = offerW;
        offers[offerCount].offerStone = offerS;
        offers[offerCount].offerIron = offerI;
        offers[offerCount].requestFood = requestF;
        offers[offerCount].requestWood = requestW;
        offers[offerCount].requestStone = requestS;
        offers[offerCount].requestIron = requestI;
        offers[offerCount].smuggling = smuggling;
        offers[offerCount].active = true;
        offerCount++;
        cout << "Trade proposed to Player " << recipientId << ".\n";
    }
    else {
        cout << "Cannot propose trade: invalid parameters or offer limit reached.\n";
    }
}

void Market::acceptTrade(int offerIndex, Player* players, Diplomacy* diplomacy) {
    if (offerIndex < 0 || offerIndex >= offerCount || !offers[offerIndex].active) {
        cout << "Invalid trade offer.\n";
        return;
    }
    TradeOffer& offer = offers[offerIndex];
    Player& sender = players[offer.senderId];
    Player& recipient = players[offer.recipientId];

    if (sender.resources->hasResources(offer.offerFood, offer.offerWood, offer.offerStone, offer.offerIron) &&
        recipient.resources->hasResources(offer.requestFood, offer.requestWood, offer.requestStone, offer.requestIron)) {
        if (offer.smuggling && (rand() % 100) < 30) {
            cout << "Smuggling detected! Trade canceled, penalties applied.\n";
            sender.resources->consumeResources(offer.offerFood / 2, offer.offerWood / 2, offer.offerStone / 2, offer.offerIron / 2);
            recipient.resources->consumeResources(offer.requestFood / 2, offer.requestWood / 2, offer.requestStone / 2, offer.requestIron / 2);
            sender.leadership->reduceApproval(10);
            recipient.leadership->reduceApproval(10);
            diplomacy->breakTreaty(offer.senderId, offer.recipientId);
        }
        else {
            sender.resources->consumeResources(offer.offerFood, offer.offerWood, offer.offerStone, offer.offerIron);
            recipient.resources->gatherResources(offer.offerFood, offer.offerWood, offer.offerStone, offer.offerIron);
            recipient.resources->consumeResources(offer.requestFood, offer.requestWood, offer.requestStone, offer.requestIron);
            sender.resources->gatherResources(offer.requestFood, offer.requestWood, offer.requestStone, offer.requestIron);
            cout << "Trade completed successfully.\n";
        }
        offer.active = false;
    }
    else {
        cout << "Insufficient resources for trade.\n";
    }
}

void Market::viewOffers(int playerId) {
    cout << "Trade offers for Player " << playerId << ":\n";
    bool hasOffers = false;
    for (int i = 0; i < offerCount; i++) {
        if (offers[i].active && offers[i].recipientId == playerId) {
            cout << "Offer " << i << " from Player " << offers[i].senderId << ":\n";
            cout << "Offers: Food=" << offers[i].offerFood << ", Wood=" << offers[i].offerWood
                << ", Stone=" << offers[i].offerStone << ", Iron=" << offers[i].offerIron << "\n";
            cout << "Requests: Food=" << offers[i].requestFood << ", Wood=" << offers[i].requestWood
                << ", Stone=" << offers[i].requestStone << ", Iron=" << offers[i].requestIron << "\n";
            cout << "Smuggling: " << (offers[i].smuggling ? "Yes" : "No") << "\n";
            hasOffers = true;
        }
    }
    if (!hasOffers) {
        cout << "No trade offers.\n";
    }
}

void Market::saveToFile(ofstream& outFile) {
    outFile << "# Market\n";
    outFile << "OfferCount: " << offerCount << "\n";
    for (int i = 0; i < offerCount; i++) {
        if (offers[i].active) {
            outFile << "Offer" << i << "_Sender: " << offers[i].senderId << "\n";
            outFile << "Offer" << i << "_Recipient: " << offers[i].recipientId << "\n";
            outFile << "Offer" << i << "_Food: " << offers[i].offerFood << "\n";
            outFile << "Offer" << i << "_Wood: " << offers[i].offerWood << "\n";
            outFile << "Offer" << i << "_Stone: " << offers[i].offerStone << "\n";
            outFile << "Offer" << i << "_Iron: " << offers[i].offerIron << "\n";
            outFile << "Offer" << i << "_RequestFood: " << offers[i].requestFood << "\n";
            outFile << "Offer" << i << "_RequestWood: " << offers[i].requestWood << "\n";
            outFile << "Offer" << i << "_RequestStone: " << offers[i].requestStone << "\n";
            outFile << "Offer" << i << "_RequestIron: " << offers[i].requestIron << "\n";
            outFile << "Offer" << i << "_Smuggling: " << offers[i].smuggling << "\n";
        }
    }
    outFile << "\n";
}

void Market::loadFromFile(ifstream& inFile) {
    string line;
    bool oldFormat = false;
    streampos startPos = inFile.tellg();
    getline(inFile, line);
    inFile.seekg(startPos);
    if (line.find("OfferCount:") != 0) {
        oldFormat = true;
        inFile >> offerCount;
        inFile.ignore();
        for (int i = 0; i < offerCount; i++) {
            inFile >> offers[i].senderId >> offers[i].recipientId
                >> offers[i].offerFood >> offers[i].offerWood >> offers[i].offerStone >> offers[i].offerIron
                >> offers[i].requestFood >> offers[i].requestWood >> offers[i].requestStone >> offers[i].requestIron
                >> offers[i].smuggling;
            offers[i].active = true;
            inFile.ignore();
        }
    }
    else {
        while (getline(inFile, line)) {
            if (line.find("OfferCount:") == 0) {
                inFile >> offerCount;
                inFile.ignore();
                break;
            }
        }
        for (int i = 0; i < offerCount; i++) {
            while (getline(inFile, line)) {
                if (line.find("Offer" + to_string(i) + "_Sender:") == 0) {
                    inFile >> offers[i].senderId;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Recipient:") == 0) {
                    inFile >> offers[i].recipientId;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Food:") == 0) {
                    inFile >> offers[i].offerFood;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Wood:") == 0) {
                    inFile >> offers[i].offerWood;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Stone:") == 0) {
                    inFile >> offers[i].offerStone;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Iron:") == 0) {
                    inFile >> offers[i].offerIron;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_RequestFood:") == 0) {
                    inFile >> offers[i].requestFood;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_RequestWood:") == 0) {
                    inFile >> offers[i].requestWood;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_RequestStone:") == 0) {
                    inFile >> offers[i].requestStone;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_RequestIron:") == 0) {
                    inFile >> offers[i].requestIron;
                    inFile.ignore();
                }
                else if (line.find("Offer" + to_string(i) + "_Smuggling:") == 0) {
                    inFile >> offers[i].smuggling;
                    offers[i].active = true;
                    inFile.ignore();
                    break;
                }
            }
        }
    }
}

Market::~Market() {
    cout << "Market system destroyed.\n";
}