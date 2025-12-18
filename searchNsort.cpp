#include "searchNsort.h"
#include <algorithm>

using namespace std;

// ==================== LOAN SEARCH ====================

Loan SearchNSort::searchLoanByID(const string& loanId, const LinkedList<Loan>& loans) {
    int left = 0, right = loans.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (loans[mid].getLoanId() == loanId) return loans[mid];
        if (loans[mid].getLoanId() < loanId) left = mid + 1;
        else right = mid - 1;
    }
    return Loan(0, 0, 0, "", "", ""); 
}

LinkedList<Loan> SearchNSort::filterLoansByUserID(const string& userId, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getUserId() == userId) result.push_back(loan);
    }
    return result;
}

LinkedList<Loan> SearchNSort::filterLoansByInterestRate(double minRate, double maxRate, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getInterestRate() >= minRate && loan.getInterestRate() <= maxRate)
            result.push_back(loan);
    }
    return result;
}

LinkedList<Loan> SearchNSort::filterLoansByPrincipal(double minPrincipal, double maxPrincipal, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getPrincipal() >= minPrincipal && loan.getPrincipal() <= maxPrincipal)
            result.push_back(loan);
    }
    return result;
}

LinkedList<Loan> SearchNSort::filterLoansByOutstandingBalance(double minAmount, double maxAmount, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    LinkedList<Payment> empty;
    for (const auto& loan : loans) {
        double balance = loan.calculateOutstandingBalance(empty);
        if (balance >= minAmount && balance <= maxAmount) result.push_back(loan);
    }
    return result;
}

LinkedList<Loan> SearchNSort::filterLoansByTermYears(int minYears, int maxYears, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getTermYears() >= minYears && loan.getTermYears() <= maxYears)
            result.push_back(loan);
    }
    return result;
}

LinkedList<Loan> SearchNSort::filterLoansByDateRange(const string& startDate, const string& endDate, const LinkedList<Loan>& loans) {
    LinkedList<Loan> result;
    for (const auto& loan : loans) {
        if (loan.getDate() >= startDate && loan.getDate() <= endDate)
            result.push_back(loan);
    }
    return result;
}

// ==================== LOAN SORT ====================

void SearchNSort::sortLoansByPrincipal(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getPrincipal() <= b.getPrincipal();
    });
}

void SearchNSort::sortLoansByInterestRate(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getInterestRate() <= b.getInterestRate();
    });
}

void SearchNSort::sortLoansByOutstandingBalance(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        LinkedList<Payment> empty;
        return a.calculateOutstandingBalance(empty) <= b.calculateOutstandingBalance(empty);
    });
}

void SearchNSort::sortLoansByTermYears(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getTermYears() <= b.getTermYears();
    });
}

void SearchNSort::sortLoansByDate(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getDate() <= b.getDate();
    });
}

void SearchNSort::sortLoansByLoanID(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getLoanId() <= b.getLoanId();
    });
}

void SearchNSort::sortLoansByUserID(LinkedList<Loan>& loans) {
    if (loans.empty()) return;
    quickSortRecursive(loans, 0, loans.size() - 1, [](const Loan& a, const Loan& b) {
        return a.getUserId() <= b.getUserId();
    });
}

// ==================== PAYMENT SEARCH ====================

Payment SearchNSort::searchPaymentByLoanID(const string& loanId, const LinkedList<Payment>& payments) {
    for (const auto& p : payments) {
        if (p.getLoanId() == loanId) return p;
    }
    return Payment(0, "", "", "");
}

Payment SearchNSort::searchPaymentByDate(const string& date, const LinkedList<Payment>& payments) {
    for (const auto& p : payments) {
        if (p.getPaymentDate() == date) return p;
    }
    return Payment(0, "", "", "");
}

LinkedList<Payment> SearchNSort::filterPaymentsByAmountRange(double min, double max, const LinkedList<Payment>& payments) {
    LinkedList<Payment> result;
    for (const auto& p : payments) {
        if (p.getAmount() >= min && p.getAmount() <= max) result.push_back(p);
    }
    return result;
}

LinkedList<Payment> SearchNSort::filterPaymentsByUserID(const string& userId, const LinkedList<Payment>& payments, const LinkedList<Loan>& loans) {
    LinkedList<Payment> result;
    LinkedList<string> userLoanIds;
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

void SearchNSort::sortPaymentsByPaymentID(LinkedList<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getPaymentId() <= b.getPaymentId();
    });
}

void SearchNSort::sortPaymentsByLoanID(LinkedList<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getLoanId() <= b.getLoanId();
    });
}

void SearchNSort::sortPaymentsByDate(LinkedList<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getPaymentDate() <= b.getPaymentDate();
    });
}

void SearchNSort::sortPaymentsByAmount(LinkedList<Payment>& payments) {
    if (payments.empty()) return;
    quickSortRecursive(payments, 0, payments.size() - 1, [](const Payment& a, const Payment& b) {
        return a.getAmount() <= b.getAmount();
    });
}

// ==================== USER SEARCH ====================

User SearchNSort::searchUserByID(const string& userId, const LinkedList<User>& users) {
    int left = 0, right = users.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (users[mid].getUserId() == userId) return users[mid];
        if (users[mid].getUserId() < userId) left = mid + 1;
        else right = mid - 1;
    }
    return User("", "", "", "", Role::BORROWER);
}

User SearchNSort::searchUserByEmail(const string& email, const LinkedList<User>& users) {
    for (const auto& u : users) {
        if (u.getEmail() == email) return u;
    }
    return User("", "", "", "", Role::BORROWER);
}

LinkedList<User> SearchNSort::filterUsersByRole(const Role& role, const LinkedList<User>& users) {
    LinkedList<User> result;
    for (const auto& u : users) {
        if (u.getRole() == role) result.push_back(u);
    }
    return result;
}

// ==================== USER SORT ====================

void SearchNSort::sortUsersByName(LinkedList<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getName() <= b.getName();
    });
}

void SearchNSort::sortUsersByRole(LinkedList<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getRole() <= b.getRole();
    });
}

void SearchNSort::sortUsersByEmail(LinkedList<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getEmail() <= b.getEmail();
    });
}

void SearchNSort::sortUsersByID(LinkedList<User>& users) {
    if (users.empty()) return;
    quickSortRecursive(users, 0, users.size() - 1, [](const User& a, const User& b) {
        return a.getUserId() <= b.getUserId();
    });
}