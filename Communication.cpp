#include "Stronghold.h"

using namespace std;

Message::Message() : senderId(-1), recipientId(-1), content(""), active(false) {}

Communication::Communication() : messageCount(0) {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        messages[i] = Message();
    }
}

void Communication::sendMessage(int senderId, int recipientId, string content) {
    if (messageCount < MAX_MESSAGES && senderId != recipientId && !content.empty()) {
        messages[messageCount].senderId = senderId;
        messages[messageCount].recipientId = recipientId;
        messages[messageCount].content = content;
        messages[messageCount].active = true;
        messageCount++;
        cout << "Message sent.\n";
    }
    else {
        cout << "Cannot send message: queue full, invalid recipient, or empty content.\n";
    }
}

void Communication::viewMessages(int playerId) {
    cout << "Messages for Player " << playerId << ":\n";
    bool hasMessages = false;
    for (int i = 0; i < messageCount; i++) {
        if (messages[i].active && messages[i].recipientId == playerId) {
            cout << "From Player " << messages[i].senderId << ": " << messages[i].content << "\n";
            hasMessages = true;
        }
    }
    if (!hasMessages) {
        cout << "No messages.\n";
    }
}

void Communication::saveToFile(ofstream& outFile) {
    outFile << "# Communication\n";
    outFile << "MessageCount: " << messageCount << "\n";
    for (int i = 0; i < messageCount; i++) {
        if (messages[i].active) {
            outFile << "Message" << i << "_Sender: " << messages[i].senderId << "\n";
            outFile << "Message" << i << "_Recipient: " << messages[i].recipientId << "\n";
            outFile << "Message" << i << "_Content: " << messages[i].content << "\n";
        }
    }
    outFile << "\n";
}

void Communication::loadFromFile(ifstream& inFile) {
    string line;
    bool oldFormat = false;
    streampos startPos = inFile.tellg();
    getline(inFile, line);
    inFile.seekg(startPos);
    if (line.find("MessageCount:") != 0) {
        oldFormat = true;
        inFile >> messageCount;
        inFile.ignore();
        for (int i = 0; i < messageCount; i++) {
            inFile >> messages[i].senderId >> messages[i].recipientId;
            inFile.ignore();
            getline(inFile, messages[i].content);
            messages[i].active = true;
        }
    }
    else {
        while (getline(inFile, line)) {
            if (line.find("MessageCount:") == 0) {
                inFile >> messageCount;
                inFile.ignore();
                break;
            }
        }
        for (int i = 0; i < messageCount; i++) {
            while (getline(inFile, line)) {
                if (line.find("Message" + to_string(i) + "_Sender:") == 0) {
                    inFile >> messages[i].senderId;
                    inFile.ignore();
                }
                else if (line.find("Message" + to_string(i) + "_Recipient:") == 0) {
                    inFile >> messages[i].recipientId;
                    inFile.ignore();
                }
                else if (line.find("Message" + to_string(i) + "_Content:") == 0) {
                    getline(inFile, messages[i].content);
                    messages[i].active = true;
                    break;
                }
            }
        }
    }
}

Communication::~Communication() {
    cout << "Communication system destroyed.\n";
}