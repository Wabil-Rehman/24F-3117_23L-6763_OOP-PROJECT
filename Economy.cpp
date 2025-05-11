#include "Stronghold.h"

using namespace std;

Economy::Economy() {
    income = 1000.0f;
    expenditure = 500.0f;
    taxRate = 0.1f;
}

void Economy::collectTaxes(int population) {
    if (population >= 0) {
        float taxes = population * taxRate;
        income += taxes;
        cout << "Taxes collected: " << taxes << ". Total income: " << income << ".\n";
    }
    else {
        cout << "Invalid population for tax collection.\n";
    }
}

void Economy::updateExpenditure(float amount) {
    if (amount >= 0) {
        expenditure += amount;
        cout << "Expenditure updated. New total: " << expenditure << ".\n";
    }
    else {
        cout << "Invalid expenditure amount.\n";
    }
}

void Economy::audit() {
    cout << "Economic Audit Report: \n";
    cout << "Total Income: " << income << "\n";
    cout << "Total Expenditure: " << expenditure << "\n";
    cout << "Net Wealth: " << income - expenditure << "\n";
}

void Economy::displayEconomy() {
    cout << "Income: " << income << "\n";
    cout << "Expenditure: " << expenditure << "\n";
    cout << "Tax Rate: " << taxRate * 100 << "%\n";
}

void Economy::saveToFile(ofstream& out) {
    out << "# Economy\n";
    out << "Income: " << income << "\n";
    out << "Expenditure: " << expenditure << "\n";
    out << "TaxRate: " << taxRate << "\n";
}

void Economy::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Income:") != 0) {
        oldFormat = true;
        in >> income >> expenditure >> taxRate;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Income:") == 0) {
                in >> income;
                in.ignore();
            }
            else if (line.find("Expenditure:") == 0) {
                in >> expenditure;
                in.ignore();
            }
            else if (line.find("TaxRate:") == 0) {
                in >> taxRate;
                in.ignore();
                break;
            }
        }
    }
    income = max(0.0f, income);
    expenditure = max(0.0f, expenditure);
    taxRate = max(0.0f, taxRate);
}

Economy::~Economy() {
    cout << "Economy system destroyed.\n";
}