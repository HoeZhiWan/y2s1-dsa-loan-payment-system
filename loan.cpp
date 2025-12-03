#include "loan.h"
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

Loan::Loan(double principal, double interestRate, int termYears, string userId, string loanId)
    : principal(principal), interestRate(interestRate), termYears(termYears), userId(userId), loanId(loanId)
{
    outstandingBalance = principal;
    
    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    sprintf(buffer, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    date = string(buffer);
}

double Loan::calculateMonthlyPayment() const {
    double monthlyRate = interestRate / 12.0 / 100.0;
    int numPayments = termYears * 12;
    
    if (monthlyRate == 0) {
        return principal / numPayments;
    }
    
    return principal * monthlyRate * pow(1 + monthlyRate, numPayments) / (pow(1 + monthlyRate, numPayments) - 1);
}

double Loan::calculateTotalPayment() const {
    return calculateMonthlyPayment() * termYears * 12;
}

double Loan::calculateTotalInterest() const {
    return calculateTotalPayment() - principal;
}

double Loan::calculateOutstandingBalance(const vector<Payment>& payments) const {
    double totalPaid = 0.0;
    for (const auto& payment : payments) {
        if (payment.getLoanId() == loanId) {
            totalPaid += payment.getAmount();
        }
    }
    
    double balance = calculateTotalPayment() - totalPaid;
    return balance > 0 ? balance : 0.0;
}

double Loan::getPrincipal() const {
    return principal;
}

double Loan::getInterestRate() const {
    return interestRate;
}

int Loan::getTermYears() const {
    return termYears;
}

string Loan::getUserId() const {
    return userId;
}

string Loan::getLoanId() const {
    return loanId;
}

string Loan::getDate() const {
    return date;
}

