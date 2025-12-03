#include "payment.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

Payment::Payment(double amount, string paymentDate, string loanId)
    : amount(amount), paymentDate(paymentDate), loanId(loanId)
{
    // Generate a simple random ID
    // In a real app, this should be robust or handled by DB
    int r = rand() % 10000;
    char buffer[10];
    sprintf(buffer, "P%04d", r);
    paymentId = string(buffer);
}

double Payment::getAmount() const {
    return amount;
}

string Payment::getPaymentDate() const {
    return paymentDate;
}

string Payment::getLoanId() const {
    return loanId;
}

string Payment::getPaymentId() const {
    return paymentId;
}

