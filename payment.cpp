#include "payment.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

Payment::Payment(double amount, string paymentDate, string loanId, string paymentId) {
    this->amount = amount;
    this->paymentDate = paymentDate;
    this->loanId = loanId;
    this->paymentId = paymentId;
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

