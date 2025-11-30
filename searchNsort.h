#ifndef SEARCHNSORT_H
#define SEARCHNSORT_H

#include "user.h"
#include "loan.h"
#include "payment.h"

using namespace std;

class SearchNSort
{
public:
    // Loan Search & Sort
    static Loan searchLoanByID(const string& loanId, const vector<Loan>& loans);
    static void sortLoansByInterestRate(vector<Loan>& loans);

    // Payment Search & Sort
    static Payment searchPaymentByLoanID(const string& loanId, const vector<Payment>& payments);
    static Payment searchPaymentByDate(const string& date, const vector<Payment>& payments);
    static Payment searchPaymentByAmount(double amount, const vector<Payment>& payments);
    static void sortPaymentsByDate(vector<Payment>& payments);
    static void sortPaymentsByAmount(vector<Payment>& payments);

    // User Search & Sort
    static User searchUserByID(const string& userId, const vector<User>& users);
    static vector<User> filterUsersByRole(const string& role, const vector<User>& users);
    static void sortUsersByName(vector<User>& users);
    static void sortUsersByRole(vector<User>& users);
    static void sortUsersByID(vector<User>& users);
};

#endif