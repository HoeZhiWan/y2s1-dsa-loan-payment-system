#include "searchNsort.h"
#include <algorithm>

using namespace std;

// ==================== LOAN SEARCH & SORT ====================

Loan SearchNSort::searchLoanByID(const string& loanId, const vector<Loan>& loans) {
    int left = 0, right = loans.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (loans[mid].getLoanId() == loanId) {
            return loans[mid];
        }
        if (loans[mid].getLoanId() < loanId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return Loan(0, 0, 0, "", "");
}

vector<Loan> SearchNSort::filterLoansByUserID(const string& userId, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) {
            result.push_back(loan);
        }
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByInterestRate(double minRate, double maxRate, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        double rate = loan.getInterestRate();
        if (rate >= minRate && rate <= maxRate) {
            result.push_back(loan);
        }
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByPrincipal(double minPrincipal, double maxPrincipal, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        double principal = loan.getPrincipal();
        if (principal >= minPrincipal && principal <= maxPrincipal) {
            result.push_back(loan);
        }
    }
    return result;
}

// Linear Search for Loans by Outstanding Balance Range
vector<Loan> SearchNSort::filterLoansByOutstandingBalance(double minAmount, double maxAmount, const vector<Loan>& loans) {
    vector<Loan> result;
    vector<Payment> emptyPayments;
    for (const auto& loan : loans) {
        double balance = loan.calculateOutstandingBalance(emptyPayments);
        if (balance >= minAmount && balance <= maxAmount) {
            result.push_back(loan);
        }
    }
    return result;
}

// Linear Search for Loans by Term Years Range
vector<Loan> SearchNSort::filterLoansByTermYears(int minYears, int maxYears, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        int years = loan.getTermYears();
        if (years >= minYears && years <= maxYears) {
            result.push_back(loan);
        }
    }
    return result;
}

// Linear Search for Loans by Date Range
vector<Loan> SearchNSort::filterLoansByDateRange(const string& startDate, const string& endDate, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getDate() >= startDate && loan.getDate() <= endDate) {
            result.push_back(loan); 
        }
    }
    return result;
}

// QuickSort for Loans by Principal
int partitionByPrincipal(vector<Loan>& loans, int low, int high) {
    double pivot = loans[high].getPrincipal();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getPrincipal() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByPrincipal(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByPrincipal(loans, low, high);
        quickSortByPrincipal(loans, low, pi - 1);
        quickSortByPrincipal(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByPrincipal(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByPrincipal(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by Interest Rate
int partitionByInterestRate(vector<Loan>& loans, int low, int high) {
    double pivot = loans[high].getInterestRate();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getInterestRate() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByInterestRate(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByInterestRate(loans, low, high);
        quickSortByInterestRate(loans, low, pi - 1);
        quickSortByInterestRate(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByInterestRate(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByInterestRate(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by Outstanding Balance
int partitionByOutstandingBalance(vector<Loan>& loans, int low, int high) {
    vector<Payment> emptyPayments;
    double pivot = loans[high].calculateOutstandingBalance(emptyPayments);
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].calculateOutstandingBalance(emptyPayments) <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByOutstandingBalance(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByOutstandingBalance(loans, low, high);
        quickSortByOutstandingBalance(loans, low, pi - 1);
        quickSortByOutstandingBalance(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByOutstandingBalance(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByOutstandingBalance(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by Term Years
int partitionByTermYears(vector<Loan>& loans, int low, int high) {
    int pivot = loans[high].getTermYears();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getTermYears() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByTermYears(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByTermYears(loans, low, high);
        quickSortByTermYears(loans, low, pi - 1);
        quickSortByTermYears(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByTermYears(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByTermYears(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by Date
int partitionByLoanDate(vector<Loan>& loans, int low, int high) {
    string pivot = loans[high].getDate();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getDate() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByLoanDate(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByLoanDate(loans, low, high);
        quickSortByLoanDate(loans, low, pi - 1);
        quickSortByLoanDate(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByDate(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByLoanDate(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by Loan ID
int partitionByLoanID(vector<Loan>& loans, int low, int high) {
    string pivot = loans[high].getLoanId();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getLoanId() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByLoanID(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByLoanID(loans, low, high);
        quickSortByLoanID(loans, low, pi - 1);
        quickSortByLoanID(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByLoanID(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByLoanID(loans, 0, loans.size() - 1);
    }
}

// QuickSort for Loans by User ID
int partitionByLoanUserID(vector<Loan>& loans, int low, int high) {
    string pivot = loans[high].getUserId();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (loans[j].getUserId() <= pivot) {
            i++;
            swap(loans[i], loans[j]);
        }
    }
    swap(loans[i + 1], loans[high]);
    return i + 1;
}

void quickSortByLoanUserID(vector<Loan>& loans, int low, int high) {
    if (low < high) {
        int pi = partitionByLoanUserID(loans, low, high);
        quickSortByLoanUserID(loans, low, pi - 1);
        quickSortByLoanUserID(loans, pi + 1, high);
    }
}

void SearchNSort::sortLoansByUserID(vector<Loan>& loans) {
    if (!loans.empty()) {
        quickSortByLoanUserID(loans, 0, loans.size() - 1);
    }
}

// ==================== PAYMENT SEARCH & SORT ====================

// Linear Search for Payment by Loan ID
Payment SearchNSort::searchPaymentByLoanID(const string& loanId, const vector<Payment>& payments) {
    for (const auto& payment : payments) {
        if (payment.getLoanId() == loanId) {
            return payment;
        }
    }
    return Payment(0, "", "");
}

// Linear Search for Payment by Date
Payment SearchNSort::searchPaymentByDate(const string& date, const vector<Payment>& payments) {
    for (const auto& payment : payments) {
        if (payment.getPaymentDate() == date) {
            return payment;
        }
    }
    return Payment(0, "", "");
}

// Linear Search for Payments by Amount Range
vector<Payment> SearchNSort::filterPaymentsByAmountRange(double minAmount, double maxAmount, const vector<Payment>& payments) {
    vector<Payment> result;
    for (const auto& payment : payments) {
        double amount = payment.getAmount();
        if (amount >= minAmount && amount <= maxAmount) {
            result.push_back(payment);
        }
    }
    return result;
}

// Linear Search for Payments by User ID (through loans)
vector<Payment> SearchNSort::filterPaymentsByUserID(const string& userId, const vector<Payment>& payments, const vector<Loan>& loans) {
    vector<Payment> result;
    // First find all loan IDs for this user
    vector<string> userLoanIds;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) {
            userLoanIds.push_back(loan.getLoanId());
        }
    }
    
    // Then filter payments
    for (const auto& payment : payments) {
        for (const string& id : userLoanIds) {
            if (payment.getLoanId() == id) {
                result.push_back(payment);
                break;
            }
        }
    }
    return result;
}

// QuickSort for Payments by Payment ID
int partitionByPaymentID(vector<Payment>& payments, int low, int high) {
    string pivot = payments[high].getPaymentId();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (payments[j].getPaymentId() <= pivot) {
            i++;
            swap(payments[i], payments[j]);
        }
    }
    swap(payments[i + 1], payments[high]);
    return i + 1;
}

void quickSortByPaymentID(vector<Payment>& payments, int low, int high) {
    if (low < high) {
        int pi = partitionByPaymentID(payments, low, high);
        quickSortByPaymentID(payments, low, pi - 1);
        quickSortByPaymentID(payments, pi + 1, high);
    }
}

void SearchNSort::sortPaymentsByPaymentID(vector<Payment>& payments) {
    if (!payments.empty()) {
        quickSortByPaymentID(payments, 0, payments.size() - 1);
    }
}

// QuickSort for Payments by Loan ID
int partitionByPaymentLoanID(vector<Payment>& payments, int low, int high) {
    string pivot = payments[high].getLoanId();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (payments[j].getLoanId() <= pivot) {
            i++;
            swap(payments[i], payments[j]);
        }
    }
    swap(payments[i + 1], payments[high]);
    return i + 1;
}

void quickSortByPaymentLoanID(vector<Payment>& payments, int low, int high) {
    if (low < high) {
        int pi = partitionByPaymentLoanID(payments, low, high);
        quickSortByPaymentLoanID(payments, low, pi - 1);
        quickSortByPaymentLoanID(payments, pi + 1, high);
    }
}

void SearchNSort::sortPaymentsByLoanID(vector<Payment>& payments) {
    if (!payments.empty()) {
        quickSortByPaymentLoanID(payments, 0, payments.size() - 1);
    }
}

// QuickSort for Payments by Date
int partitionByPaymentDate(vector<Payment>& payments, int low, int high) {
    string pivot = payments[high].getPaymentDate();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (payments[j].getPaymentDate() <= pivot) {
            i++;
            swap(payments[i], payments[j]);
        }
    }
    swap(payments[i + 1], payments[high]);
    return i + 1;
}

void quickSortByPaymentDate(vector<Payment>& payments, int low, int high) {
    if (low < high) {
        int pi = partitionByPaymentDate(payments, low, high);
        quickSortByPaymentDate(payments, low, pi - 1);
        quickSortByPaymentDate(payments, pi + 1, high);
    }
}

void SearchNSort::sortPaymentsByDate(vector<Payment>& payments) {
    if (!payments.empty()) {
        quickSortByPaymentDate(payments, 0, payments.size() - 1);
    }
}

// QuickSort for Payments by Amount
int partitionByPaymentAmount(vector<Payment>& payments, int low, int high) {
    double pivot = payments[high].getAmount();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (payments[j].getAmount() <= pivot) {
            i++;
            swap(payments[i], payments[j]);
        }
    }
    swap(payments[i + 1], payments[high]);
    return i + 1;
}

void quickSortByPaymentAmount(vector<Payment>& payments, int low, int high) {
    if (low < high) {
        int pi = partitionByPaymentAmount(payments, low, high);
        quickSortByPaymentAmount(payments, low, pi - 1);
        quickSortByPaymentAmount(payments, pi + 1, high);
    }
}

void SearchNSort::sortPaymentsByAmount(vector<Payment>& payments) {
    if (!payments.empty()) {
        quickSortByPaymentAmount(payments, 0, payments.size() - 1);
    }
}

// ==================== USER SEARCH & SORT ====================

// Binary Search for User by ID 
User SearchNSort::searchUserByID(const string& userId, const vector<User>& users) {
    int left = 0, right = users.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (users[mid].getUserId() == userId) {
            return users[mid];
        }
        if (users[mid].getUserId() < userId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return User("", "", "", "", Role::BORROWER);
}

// Linear Search for User by Email
User SearchNSort::searchUserByEmail(const string& email, const vector<User>& users) {
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            return user;
        }
    }
    return User("", "", "", "", Role::BORROWER);
}

// Linear Search for Users by Role
vector<User> SearchNSort::filterUsersByRole(const string& role, const vector<User>& users) {
    vector<User> result;
    for (const auto& user : users) {
        if (user.getRole() == role) {
            result.push_back(user);
        }
    }
    return result;
}

// QuickSort for Users by Name
int partitionByName(vector<User>& users, int low, int high) {
    string pivot = users[high].getName();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (users[j].getName() <= pivot) {
            i++;
            swap(users[i], users[j]);
        }
    }
    swap(users[i + 1], users[high]);
    return i + 1;
}

void quickSortByName(vector<User>& users, int low, int high) {
    if (low < high) {
        int pi = partitionByName(users, low, high);
        quickSortByName(users, low, pi - 1);
        quickSortByName(users, pi + 1, high);
    }
}

void SearchNSort::sortUsersByName(vector<User>& users) {
    if (!users.empty()) {
        quickSortByName(users, 0, users.size() - 1);
    }
}

// QuickSort for Users by Role
int partitionByRole(vector<User>& users, int low, int high) {
    string pivot = users[high].getRole();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (users[j].getRole() <= pivot) {
            i++;
            swap(users[i], users[j]);
        }
    }
    swap(users[i + 1], users[high]);
    return i + 1;
}

void quickSortByRole(vector<User>& users, int low, int high) {
    if (low < high) {
        int pi = partitionByRole(users, low, high);
        quickSortByRole(users, low, pi - 1);
        quickSortByRole(users, pi + 1, high);
    }
}

void SearchNSort::sortUsersByRole(vector<User>& users) {
    if (!users.empty()) {
        quickSortByRole(users, 0, users.size() - 1);
    }
}

// QuickSort for Users by Email
int partitionByEmail(vector<User>& users, int low, int high) {
    string pivot = users[high].getEmail();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (users[j].getEmail() <= pivot) {
            i++;
            swap(users[i], users[j]);
        }
    }
    swap(users[i + 1], users[high]);
    return i + 1;
}

void quickSortByEmail(vector<User>& users, int low, int high) {
    if (low < high) {
        int pi = partitionByEmail(users, low, high);
        quickSortByEmail(users, low, pi - 1);
        quickSortByEmail(users, pi + 1, high);
    }
}

void SearchNSort::sortUsersByEmail(vector<User>& users) {
    if (!users.empty()) {
        quickSortByEmail(users, 0, users.size() - 1);
    }
}

// QuickSort for Users by ID
int partitionByUserID(vector<User>& users, int low, int high) {
    string pivot = users[high].getUserId();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (users[j].getUserId() <= pivot) {
            i++;
            swap(users[i], users[j]);
        }
    }
    swap(users[i + 1], users[high]);
    return i + 1;
}

void quickSortByUserID(vector<User>& users, int low, int high) {
    if (low < high) {
        int pi = partitionByUserID(users, low, high);
        quickSortByUserID(users, low, pi - 1);
        quickSortByUserID(users, pi + 1, high);
    }
}

void SearchNSort::sortUsersByID(vector<User>& users) {
    if (!users.empty()) {
        quickSortByUserID(users, 0, users.size() - 1);
    }
}
