#ifndef LOANSYSTEM_H
#define LOANSYSTEM_H

#include "user.h"
#include "loan.h"
#include "payment.h"
#include "searchNsort.h"
#include "fileHandling.h"
#include "menu.h"

#include "LinkedList.h"
#include "paymentQueue.h"

using namespace std;

class LoanSystem
{
private:
    LinkedList<User> users;
    LinkedList<Loan> loans;
    LinkedList<Payment> payments;
    PaymentQueue paymentQueue;
    LinkedList<Payment> getPaymentsForLoan(const string& loanId) const;

public:
    static void initialize();
    static void shutdown();

    // Menu
    void menuLoop();

    // Functions
    void createLoan();
    void makePayment(User* currentUser);
    void viewPaymentHistory(const string& filterUserId = "");
    void viewUpcomingPayments(const string& filterUserId = "");
    void viewLoans(const string& filterUserId = "");
    void viewUsers();
    void manageUsers();

    // Login
    User* login(const string& userId, const string& password);

    // Handle Data
    void loadData();
    void saveData();

    //Queue payments for processing
    void enqueuePayment(const Payment& payment);  // borrower enQueue
    void processNextPayment();                    // admin deQueue one
    void processAllPayments();                    // admin deQueue all
    void displayPendingPayments() const;          // (optional) print queue
};

#endif