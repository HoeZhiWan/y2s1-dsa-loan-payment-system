#include "searchNsort.h"
#include <algorithm>

using namespace std;

// ==================== LOAN SEARCH ====================

Loan SearchNSort::searchLoanByID(const string& loanId, const vector<Loan>& loans) {
    int left = 0, right = loans.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (loans[mid].getLoanId() == loanId) return loans[mid];
        if (loans[mid].getLoanId() < loanId) left = mid + 1;
        else right = mid - 1;
    }
    return Loan(0, 0, 0, "", "", ""); 
}

vector<Loan> SearchNSort::filterLoansByUserID(const string& userId, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) result.push_back(loan);
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByInterestRate(double minRate, double maxRate, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getInterestRate() >= minRate && loan.getInterestRate() <= maxRate)
            result.push_back(loan);
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByPrincipal(double minPrincipal, double maxPrincipal, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getPrincipal() >= minPrincipal && loan.getPrincipal() <= maxPrincipal)
            result.push_back(loan);
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByOutstandingBalance(double minAmount, double maxAmount, const vector<Loan>& loans) {
    vector<Loan> result;
    vector<Payment> empty;
    for (const auto& loan : loans) {
        double balance = loan.calculateOutstandingBalance(empty);
        if (balance >= minAmount && balance <= maxAmount) result.push_back(loan);
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByTermYears(int minYears, int maxYears, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getTermYears() >= minYears && loan.getTermYears() <= maxYears)
            result.push_back(loan);
    }
    return result;
}

vector<Loan> SearchNSort::filterLoansByDateRange(const string& startDate, const string& endDate, const vector<Loan>& loans) {
    vector<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getDate() >= startDate && loan.getDate() <= endDate)
            result.push_back(loan);
    }
    return result;
}

// ==================== LOAN SORT ====================

void SearchNSort::sortLoansByPrincipal(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getPrincipal() <= b.getPrincipal();
    });
}

void SearchNSort::sortLoansByInterestRate(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getInterestRate() <= b.getInterestRate();
    });
}

void SearchNSort::sortLoansByOutstandingBalance(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        vector<Payment> empty;
        return a.calculateOutstandingBalance(empty) <= b.calculateOutstandingBalance(empty);
    });
}

void SearchNSort::sortLoansByTermYears(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getTermYears() <= b.getTermYears();
    });
}

void SearchNSort::sortLoansByDate(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getDate() <= b.getDate();
    });
}

void SearchNSort::sortLoansByLoanID(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getLoanId() <= b.getLoanId();
    });
}

void SearchNSort::sortLoansByUserID(vector<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getUserId() <= b.getUserId();
    });
}

// ==================== PAYMENT SEARCH ====================

Payment SearchNSort::searchPaymentByLoanID(const string& loanId, const vector<Payment>& payments) {
    for (const auto& p : payments) {
        if (p.getLoanId() == loanId) return p;
    }
    return Payment(0, "", "", "");
}

Payment SearchNSort::searchPaymentByDate(const string& date, const vector<Payment>& payments) {
    for (const auto& p : payments) {
        if (p.getPaymentDate() == date) return p;
    }
    return Payment(0, "", "", "");
}

vector<Payment> SearchNSort::filterPaymentsByAmountRange(double min, double max, const vector<Payment>& payments) {
    vector<Payment> result;
    for (const auto& p : payments) {
        if (p.getAmount() >= min && p.getAmount() <= max) result.push_back(p);
    }
    return result;
}

vector<Payment> SearchNSort::filterPaymentsByUserID(const string& userId, const vector<Payment>& payments, const vector<Loan>& loans) {
    vector<Payment> result;
    vector<string> userLoanIds;
    for (const auto& l : loans) {
        if (l.getUserId() == userId) userLoanIds.push_back(l.getLoanId());
    }
    for (const auto& p : payments) {
        for (const string& id : userLoanIds) {
            if (p.getLoanId() == id) {
                result.push_back(p);
                break;
            }
        }
    }
    return result;
}

// ==================== PAYMENT SORT ====================

void SearchNSort::sortPaymentsByPaymentID(vector<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getPaymentId() <= b.getPaymentId();
    });
}

void SearchNSort::sortPaymentsByLoanID(vector<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getLoanId() <= b.getLoanId();
    });
}

void SearchNSort::sortPaymentsByDate(vector<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getPaymentDate() <= b.getPaymentDate();
    });
}

void SearchNSort::sortPaymentsByAmount(vector<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getAmount() <= b.getAmount();
    });
}

// ==================== USER SEARCH ====================

User SearchNSort::searchUserByID(const string& userId, const vector<User>& users) {
    int left = 0, right = users.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (users[mid].getUserId() == userId) return users[mid];
        if (users[mid].getUserId() < userId) left = mid + 1;
        else right = mid - 1;
    }
    return User("", "", "", "", Role::BORROWER);
}

User SearchNSort::searchUserByEmail(const string& email, const vector<User>& users) {
    for (const auto& u : users) {
        if (u.getEmail() == email) return u;
    }
    return User("", "", "", "", Role::BORROWER);
}

vector<User> SearchNSort::filterUsersByRole(const Role& role, const vector<User>& users) {
    vector<User> result;
    for (const auto& u : users) {
        if (u.getRole() == role) result.push_back(u);
    }
    return result;
}

// ==================== USER SORT ====================

void SearchNSort::sortUsersByName(vector<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getName() <= b.getName();
    });
}

void SearchNSort::sortUsersByRole(vector<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getRole() <= b.getRole();
    });
}

void SearchNSort::sortUsersByEmail(vector<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getEmail() <= b.getEmail();
    });
}

void SearchNSort::sortUsersByID(vector<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getUserId() <= b.getUserId();
    });
}