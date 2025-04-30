#include "Stronghold.h"

// Constructor
Bank::Bank() {
    treasury = 5000.0;
    loanDebt = 1000.0;
    interestRate = 0.05;
}

// Take a loan from the bank
void Bank::takeLoan(float amount) {
    loanDebt += amount;
    treasury += amount;
    cout << "Loan taken: " << amount << ". Current debt: " << loanDebt << ".\n";
}

// Repay a loan
void Bank::repayLoan(float amount) {
    if (loanDebt >= amount) {
        loanDebt -= amount;
        treasury -= amount;
        cout << "Loan repaid: " << amount << ". Remaining debt: " << loanDebt << ".\n";
    }
    else {
        cout << "Repayment exceeds debt.\n";
    }
}

// Perform a bank audit
void Bank::audit() {
    cout << "Audit report: \n";
    cout << "Treasury: " << treasury << "\n";
    cout << "Loan Debt: " << loanDebt << "\n";
    cout << "Interest Rate: " << interestRate << "\n";
}

// Display bank details
void Bank::displayBank() {
    cout << "Bank Treasury: " << treasury << "\n";
    cout << "Loan Debt: " << loanDebt << "\n";
}

// Save bank state to file
void Bank::saveToFile(ofstream& out) {
    out << treasury << " " << loanDebt << " " << interestRate << "\n";
}

// Load bank state from file
void Bank::loadFromFile(ifstream& in) {
    in >> treasury >> loanDebt >> interestRate;
}

// Destructor
Bank::~Bank() {
    cout << "Bank destroyed.\n";
}
