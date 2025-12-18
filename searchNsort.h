#ifndef SEARCHNSORT_H
#define SEARCHNSORT_H

#include <algorithm>

#include "user.h"
#include "loan.h"
#include "payment.h"
#include "LinkedList.h"

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
    static int partition(LinkedList<T>& arr, int low, int high, Comparator comp) {
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
    static void quickSortRecursive(LinkedList<T>& arr, int low, int high, Comparator comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortRecursive(arr, low, pi - 1, comp);
            quickSortRecursive(arr, pi + 1, high, comp);
        }
    }

public:
    // Loan Search & Sort
    static Loan searchLoanByID(const string& loanId, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByUserID(const string& userId, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByInterestRate(double minRate, double maxRate, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByPrincipal(double minPrincipal, double maxPrincipal, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByOutstandingBalance(double minAmount, double maxAmount, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByTermYears(int minYears, int maxYears, const LinkedList<Loan>& loans);
    static LinkedList<Loan> filterLoansByDateRange(const string& startDate, const string& endDate, const LinkedList<Loan>& loans);
    static void sortLoansByPrincipal(LinkedList<Loan>& loans);
    static void sortLoansByInterestRate(LinkedList<Loan>& loans);
    static void sortLoansByOutstandingBalance(LinkedList<Loan>& loans);
    static void sortLoansByTermYears(LinkedList<Loan>& loans);
    static void sortLoansByDate(LinkedList<Loan>& loans);
    static void sortLoansByLoanID(LinkedList<Loan>& loans);
    static void sortLoansByUserID(LinkedList<Loan>& loans);

    // Payment Search & Sort
    static Payment searchPaymentByLoanID(const string& loanId, const LinkedList<Payment>& payments);
    static Payment searchPaymentByDate(const string& date, const LinkedList<Payment>& payments);
    static LinkedList<Payment> filterPaymentsByAmountRange(double minAmount, double maxAmount, const LinkedList<Payment>& payments);
    static LinkedList<Payment> filterPaymentsByUserID(const string& userId, const LinkedList<Payment>& payments, const LinkedList<Loan>& loans);
    static void sortPaymentsByPaymentID(LinkedList<Payment>& payments);
    static void sortPaymentsByLoanID(LinkedList<Payment>& payments);
    static void sortPaymentsByDate(LinkedList<Payment>& payments);
    static void sortPaymentsByAmount(LinkedList<Payment>& payments);

    // User Search & Sort
    static User searchUserByID(const string& userId, const LinkedList<User>& users);
    static User searchUserByEmail(const string& email, const LinkedList<User>& users);
    static LinkedList<User> filterUsersByRole(const Role& role, const LinkedList<User>& users);
    static void sortUsersByName(LinkedList<User>& users);
    static void sortUsersByRole(LinkedList<User>& users);
    static void sortUsersByEmail(LinkedList<User>& users);
    static void sortUsersByID(LinkedList<User>& users);
};

#endif