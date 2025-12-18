#include <fstream>
#include <sstream>

#include "fileHandling.h"
#include "searchNsort.h"
#include "user.h"
#include "loan.h"
#include "payment.h"
#include "LinkedList.h"

using namespace std;

void FileHandling::loadUsers(const string& filename, LinkedList<User>& users) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    users.clear();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string userId, name, email, password, roleStr;
        
        getline(ss, userId, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, roleStr, ',');
        
        Role role = (roleStr == "ADMIN") ? Role::ADMIN : Role::BORROWER;
        users.push_back(User(userId, name, email, password, role));
    }

    SearchNSort::sortUsersByID(users);
    
    file.close();
}

void FileHandling::saveUsers(const string& filename, const LinkedList<User>& users) {
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

void FileHandling::loadLoans(const string& filename, LinkedList<Loan>& loans) {
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
        string date;
        getline(ss, date, ',');
        
        loans.push_back(Loan(principal, interestRate, termYears, userId, loanId, date));
    }

    SearchNSort::sortLoansByLoanID(loans);
    
    file.close();
}

void FileHandling::saveLoans(const string& filename, const LinkedList<Loan>& loans) {
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    for (const auto& loan : loans) {
        file << loan.getLoanId() << ","
             << loan.getUserId() << ","
             << loan.getPrincipal() << ","
             << loan.getInterestRate() << ","
             << loan.getTermYears() << ","
             << loan.getDate() << "\n";
    }
    
    file.close();
}

void FileHandling::loadPayments(const string& filename, LinkedList<Payment>& payments) {
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

    SearchNSort::sortPaymentsByPaymentID(payments);
    
    file.close();
}

void FileHandling::savePayments(const string& filename, const LinkedList<Payment>& payments) {
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
