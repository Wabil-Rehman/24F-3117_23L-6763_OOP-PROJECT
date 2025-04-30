#include "Stronghold.h"

// Constructor
Economy::Economy() {
    income = 1000.0;
    expenditure = 500.0;
    taxRate = 0.1;
}

// Calculate taxes collected from the population
void Economy::collectTaxes(int population) {
    float taxes = population * taxRate;
    income += taxes;
    cout << "Taxes collected: " << taxes << ". Total income: " << income << ".\n";
}

// Update economy expenditures (e.g., military spending)
void Economy::updateExpenditure(float amount) {
    expenditure += amount;
    cout << "Expenditure updated. New total: " << expenditure << ".\n";
}

// Perform an economic audit
void Economy::audit() {
    cout << "Economic Audit Report: \n";
    cout << "Total Income: " << income << "\n";
    cout << "Total Expenditure: " << expenditure << "\n";
    cout << "Net Wealth: " << income - expenditure << "\n";
}

// Display economy details
void Economy::displayEconomy() {
    cout << "Income: " << income << "\n";
    cout << "Expenditure: " << expenditure << "\n";
    cout << "Tax Rate: " << taxRate * 100 << "%\n";
}

// Save to file
void Economy::saveToFile(ofstream& out) {
    out << income << " " << expenditure << " " << taxRate << "\n";
}

// Load from file
void Economy::loadFromFile(ifstream& in) {
    in >> income >> expenditure >> taxRate;
}

// Destructor
Economy::~Economy() {
    cout << "Economy system destroyed.\n";
}
