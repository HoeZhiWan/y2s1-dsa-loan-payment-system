#include "fileHandling.h"
#include <fstream>
#include <sstream>

#include "searchNsort.h"

using namespace std;

void FileHandling::loadUsers(const string& filename, vector<User>& users) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    users.clear();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string userId, name, email, passwordHash, roleStr;
        
        getline(ss, userId, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, passwordHash, ',');
        getline(ss, roleStr, ',');
        
        Role role = (roleStr == "ADMIN") ? Role::ADMIN : Role::BORROWER;
        users.push_back(User(userId, name, email, passwordHash, role));
    }
    
    file.close();
}

void FileHandling::saveUsers(const string& filename, const vector<User>& users) {
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    for (const auto& user : users) {
        file << user.getUserId() << ","
             << user.getName() << ","
             << user.getEmail() << ","
             << user.getPassword() << ","
             << (user.getRole() == Role::ADMIN ? "ADMIN" : "BORROWER") << "\n";
    }
    
    file.close();
}

void FileHandling::loadLoans(const string& filename, vector<Loan>& loans) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    loans.clear();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string loanId, userId;
        double principal, interestRate;
        int termYears;
        
        string temp;
        getline(ss, loanId, ',');
        getline(ss, userId, ',');
        getline(ss, temp, ',');
        principal = stod(temp);
        getline(ss, temp, ',');
        interestRate = stod(temp);
        getline(ss, temp, ',');
        termYears = stoi(temp);
        
        loans.push_back(Loan(principal, interestRate, termYears, userId, loanId));
    }

    SearchNSort::sortLoansByLoanID(loans);
    
    file.close();
}

void FileHandling::saveLoans(const string& filename, const vector<Loan>& loans) {
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    for (const auto& loan : loans) {
        file << loan.getLoanId() << ","
             << loan.getUserId() << ","
             << loan.getPrincipal() << ","
             << loan.getInterestRate() << ","
             << loan.getTermYears() << "\n";
    }
    
    file.close();
}

void FileHandling::loadPayments(const string& filename, vector<Payment>& payments) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    payments.clear();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string paymentId, loanId, date;
        double amount;
        
        string temp;
        getline(ss, paymentId, ',');
        getline(ss, loanId, ',');
        getline(ss, date, ',');
        getline(ss, temp, ',');
        amount = stod(temp);
        
        payments.push_back(Payment(amount, date, loanId, paymentId));
    }
    
    file.close();
}

void FileHandling::savePayments(const string& filename, const vector<Payment>& payments) {
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    for (const auto& payment : payments) {
        file << payment.getPaymentId() << ","
             << payment.getLoanId() << ","
             << payment.getPaymentDate() << ","
             << payment.getAmount() << "\n";
    }
    
    file.close();
}
