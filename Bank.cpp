#include "Stronghold.h"

using namespace std;

Bank::Bank() {
    treasury = 5000.0f;
    loanDebt = 1000.0f;
    interestRate = 0.05f;
}

void Bank::takeLoan(float amount) {
    if (amount > 0) {
        loanDebt += amount;
        treasury += amount;
        cout << "Loan taken: " << amount << ". Current debt: " << loanDebt << ".\n";
    }
    else {
        cout << "Invalid loan amount.\n";
    }
}

void Bank::repayLoan(float amount) {
    if (amount > 0 && amount <= loanDebt && amount <= treasury) {
        loanDebt -= amount;
        treasury -= amount;
        cout << "Loan repaid: " << amount << ". Remaining debt: " << loanDebt << ".\n";
    }
    else {
        cout << "Invalid repayment amount or insufficient funds.\n";
    }
}

void Bank::audit() {
    cout << "Audit report: \n";
    cout << "Treasury: " << treasury << "\n";
    cout << "Loan Debt: " << loanDebt << "\n";
    cout << "Interest Rate: " << interestRate << "\n";
}

void Bank::displayBank() {
    cout << "Bank Treasury: " << treasury << "\n";
    cout << "Loan Debt: " << loanDebt << "\n";
}

void Bank::saveToFile(ofstream& out) {
    out << "# Bank\n";
    out << "Treasury: " << treasury << "\n";
    out << "LoanDebt: " << loanDebt << "\n";
    out << "InterestRate: " << interestRate << "\n";
}

void Bank::loadFromFile(ifstream& in) {
    string line;
    bool oldFormat = false;
    streampos startPos = in.tellg();
    getline(in, line);
    in.seekg(startPos);
    if (line.find("Treasury:") != 0) {
        oldFormat = true;
        in >> treasury >> loanDebt >> interestRate;
        in.ignore();
    }
    else {
        while (getline(in, line)) {
            if (line.find("Treasury:") == 0) {
                in >> treasury;
                in.ignore();
            }
            else if (line.find("LoanDebt:") == 0) {
                in >> loanDebt;
                in.ignore();
            }
            else if (line.find("InterestRate:") == 0) {
                in >> interestRate;
                in.ignore();
                break;
            }
        }
    }
    treasury = max(0.0f, treasury);
    loanDebt = max(0.0f, loanDebt);
    interestRate = max(0.0f, interestRate);
}

Bank::~Bank() {
    cout << "Bank destroyed.\n";
}