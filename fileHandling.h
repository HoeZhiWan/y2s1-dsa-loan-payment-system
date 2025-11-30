#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "user.h"
#include "loan.h"
#include "payment.h"

using namespace std;

class FileHandling
{
public:
    static void loadUsers(const string& filename, vector<User>& users);
    static void saveUsers(const string& filename, const vector<User>& users);

    static void loadLoans(const string& filename, vector<Loan>& loans);
    static void saveLoans(const string& filename, const vector<Loan>& loans);

    static void loadPayments(const string& filename, vector<Payment>& payments);
    static void savePayments(const string& filename, const vector<Payment>& payments);
};


#endif