#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

using namespace std;

class Payment
{
private:
    double amount;         // The amount of the payment
    string paymentDate;    // Date of the payment
    string loanId;         // ID of the associated loan

public:
    Payment(double amount, string paymentDate, string loanId);

    double getAmount() const;
    string getPaymentDate() const;
    string getLoanId() const;
};

#endif