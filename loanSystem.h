#ifndef LOANSYSTEM_H
#define LOANSYSTEM_H

#include "user.h"
#include "loan.h"
#include "payment.h"
#include "searchNsort.h"
#include "fileHandling.h"
#include "menu.h"

#include <vector>

using namespace std;

class LoanSystem
{
private:
    vector<User> users;
    vector<Loan> loans;
    vector<Payment> payments;

public:
    static void initialize();
    static void shutdown();

    // Menu
    void menuLoop();

    // Functions
    void createLoan();
    void makePayment(User* currentUser);
    void viewPaymentHistory(const string& filterUserId = "");
    void viewUpcomingPayments();
    void approveLoan();
    void administerUsers();
    void manageUsers();

    // Login
    User* login(const string& userId, const string& password);
};

#endif