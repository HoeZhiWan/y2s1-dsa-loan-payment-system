#ifndef SEARCHNSORT_H
#define SEARCHNSORT_H

#include <vector>
#include <algorithm>

#include "user.h"
#include "loan.h"
#include "payment.h"

using namespace std;

// Searching Algorithms Used:
// - Linear Search
// 	loan: date[], userId[]
// 	user: name[]
// 	payment: paymentId[]
// - Binary Search
// 	loan: loanId
// 	user: userId
// 	paymentL amount, userId, loanId, date

// Sorting Algorithms Used:
// - Quick Sort
// 	loan: loanId, date, amount, userId
// 	user: userId, name
// 	payment: amount, userId, loanId, date

class SearchNSort
{
private:
    template <typename T, typename Comparator>
    static int partition(vector<T>& arr, int low, int high, Comparator comp) {
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (comp(arr[j], pivot)) { 
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T, typename Comparator>
    static void quickSortRecursive(vector<T>& arr, int low, int high, Comparator comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortRecursive(arr, low, pi - 1, comp);
            quickSortRecursive(arr, pi + 1, high, comp);
        }
    }

public:
    // Loan Search & Sort
    static Loan searchLoanByID(const string& loanId, const vector<Loan>& loans);
    static vector<Loan> filterLoansByUserID(const string& userId, const vector<Loan>& loans);
    static vector<Loan> filterLoansByInterestRate(double minRate, double maxRate, const vector<Loan>& loans);
    static vector<Loan> filterLoansByPrincipal(double minPrincipal, double maxPrincipal, const vector<Loan>& loans);
    static vector<Loan> filterLoansByOutstandingBalance(double minAmount, double maxAmount, const vector<Loan>& loans);
    static vector<Loan> filterLoansByTermYears(int minYears, int maxYears, const vector<Loan>& loans);
    static vector<Loan> filterLoansByDateRange(const string& startDate, const string& endDate, const vector<Loan>& loans);
    static void sortLoansByPrincipal(vector<Loan>& loans);
    static void sortLoansByInterestRate(vector<Loan>& loans);
    static void sortLoansByOutstandingBalance(vector<Loan>& loans);
    static void sortLoansByTermYears(vector<Loan>& loans);
    static void sortLoansByDate(vector<Loan>& loans);
    static void sortLoansByLoanID(vector<Loan>& loans);
    static void sortLoansByUserID(vector<Loan>& loans);

    // Payment Search & Sort
    static Payment searchPaymentByLoanID(const string& loanId, const vector<Payment>& payments);
    static Payment searchPaymentByDate(const string& date, const vector<Payment>& payments);
    static vector<Payment> filterPaymentsByAmountRange(double minAmount, double maxAmount, const vector<Payment>& payments);
    static vector<Payment> filterPaymentsByUserID(const string& userId, const vector<Payment>& payments, const vector<Loan>& loans);
    static void sortPaymentsByPaymentID(vector<Payment>& payments);
    static void sortPaymentsByLoanID(vector<Payment>& payments);
    static void sortPaymentsByDate(vector<Payment>& payments);
    static void sortPaymentsByAmount(vector<Payment>& payments);

    // User Search & Sort
    static User searchUserByID(const string& userId, const vector<User>& users);
    static User searchUserByEmail(const string& email, const vector<User>& users);
    static vector<User> filterUsersByRole(const string& role, const vector<User>& users);
    static void sortUsersByName(vector<User>& users);
    static void sortUsersByRole(vector<User>& users);
    static void sortUsersByEmail(vector<User>& users);
    static void sortUsersByID(vector<User>& users);
};

#endif