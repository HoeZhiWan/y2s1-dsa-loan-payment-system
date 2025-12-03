#ifndef LOAN_H
#define LOAN_H

#include "payment.h"

#include <string>
#include <vector>

using namespace std;

class Loan
{
private:
    double principal;                   // The amount of the loan
    double interestRate;                // Annual interest rate
    int termYears;                      // Term of the loan in years
    double outstandingBalance;          // Current outstanding balance
    string date;                        // Date of the loan
    string userId;                      // ID of the user taking the loan
    string loanId;                      // ID of the loan (generated)

public:
    Loan(double principal, double interestRate, int termYears, string userId, string loanId);

    double calculateMonthlyPayment() const;
    double calculateTotalPayment() const;
    double calculateTotalInterest() const;
    double calculateOutstandingBalance(const vector<Payment>& payments) const;
    
    double getPrincipal() const;
    double getInterestRate() const;
    int getTermYears() const;
    vector<Payment> getPaymentSchedule() const;
    string getUserId() const;
    string getLoanId() const;
    string getDate() const;
};

#endif