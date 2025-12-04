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
    string paymentId;      // ID of the payment (generated)

public:
    Payment(double amount, string paymentDate, string loanId, string paymentId);

    double getAmount() const;
    string getPaymentDate() const;
    string getLoanId() const;
    string getPaymentId() const;
};

#endif