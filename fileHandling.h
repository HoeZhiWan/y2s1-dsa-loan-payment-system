#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "user.h"
#include "loan.h"
#include "payment.h"

using namespace std;

class FileHandling
{
public:
    static void loadUsers(const string& filename, LinkedList<User>& users);
    static void saveUsers(const string& filename, const LinkedList<User>& users);

    static void loadLoans(const string& filename, LinkedList<Loan>& loans);
    static void saveLoans(const string& filename, const LinkedList<Loan>& loans);

    static void loadPayments(const string& filename, LinkedList<Payment>& payments);
    static void savePayments(const string& filename, const LinkedList<Payment>& payments);
};


#endif