#include "loanSystem.h"
#include "fileHandling.h"
#include "menu.h"
#include "searchNsort.h"
#include "user.h"
#include "loan.h"
#include "payment.h"
#include "LinkedList.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>
#include <ctime>

using namespace std;

void LoanSystem::initialize()
{
    cout << "Loan System Initialized.\n";
}

void LoanSystem::shutdown()
{
    cout << "Loan System Shutdown.\n";
}

User *LoanSystem::login(const string &userId, const string &password)
{
    for (auto &user : users)
    {
        if (user.getUserId() == userId && user.getPassword() == password)
        {
            return &user;
        }
    }
    return nullptr;
}

void LoanSystem::makePayment(User *currentUser)
{
    string loanId, date;
    double amount;

    cout << "\n--- Make Payment ---\n";
    cout << "Enter Loan ID: ";
    cin >> loanId;

    // Validate Loan ID and Ownership
    bool loanFound = false;
    for (const auto &loan : loans)
    {
        if (loan.getLoanId() == loanId)
        {
            loanFound = true;
            if (currentUser->getRole() == Role::BORROWER && loan.getUserId() != currentUser->getUserId())
            {
                cout << "Error: You can only make payments for your own loans.\n";
                return;
            }
            break;
        }
    }

    if (!loanFound)
    {
        cout << "Error: Invalid Loan ID.\n";
        return;
    }

    cout << "Enter Payment Amount: RM ";
    cin >> amount;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return;
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    sprintf(buffer, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    date = string(buffer);

    int maxId = 0;
    for (const auto &p : payments)
    {
        string numPart = p.getPaymentId().substr(1); 
        try {
            int currentId = stoi(numPart);
            if (currentId > maxId) maxId = currentId;
        } catch (...) {}
    }
    int next = maxId + 1;
    string newPaymentId = string("P") + (next < 10 ? "00" : (next < 100 ? "0" : "")) + to_string(next);

    Payment newPayment(amount, date, loanId, newPaymentId);
    enqueuePayment(newPayment);
    cout << "\nPayment submitted and added to processing queue.\n";
    cout << "It will be officially recorded after an admin processes the queue.\n";
}

void LoanSystem::viewPaymentHistory(const string &filterUserId)
{
    cout << "\n--- Payment History ---\n";
    LinkedList<Payment> filteredPayments;

    if (filterUserId.empty())
    {
        filteredPayments = payments;
    }
    else
    {
        filteredPayments = SearchNSort::filterPaymentsByUserID(filterUserId, payments, loans);
    }

    if (filteredPayments.empty())
    {
        cout << "No payments found.\n";
        return;
    }

    cout << "Sort by: (D)ate, (A)mount, (N)one: ";
    char sortOpt;
    cin >> sortOpt;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        sortOpt = 'N';
    }

    if (sortOpt == 'D' || sortOpt == 'd')
    {
        SearchNSort::sortPaymentsByDate(filteredPayments);
    }
    else if (sortOpt == 'A' || sortOpt == 'a')
    {
        SearchNSort::sortPaymentsByAmount(filteredPayments);
    }

    cout << left << setw(15) << "Loan ID"
         << setw(15) << "Amount (RM )"
         << setw(20) << "Date" << "\n";
    cout << string(50, '-') << "\n";

    for (const auto &payment : filteredPayments)
    {
        cout << left << setw(15) << payment.getLoanId()
             << "RM " << setw(13) << fixed << setprecision(2) << payment.getAmount()
             << setw(20) << payment.getPaymentDate() << "\n";
    }
}

void LoanSystem::viewUpcomingPayments(const string& filterUserId)
{
    cout << "\n--- Upcoming Payments ---\n";
    if (loans.empty())
    {
        cout << "No active loans.\n";
        return;
    }

    cout << left << setw(15) << "Loan ID"
         << setw(20) << "Monthly Payment (RM )"
         << setw(20) << "Outstanding (RM )" << "\n";
    cout << string(55, '-') << "\n";

    bool foundAny = false;

    for (const auto &loan : loans)
    {
        if (!filterUserId.empty() && loan.getUserId() != filterUserId) {
            continue;
        }

        foundAny = true;
        cout << left << setw(15) << loan.getLoanId()
             << "RM " << setw(18) << fixed << setprecision(2) << loan.calculateMonthlyPayment()
             << "RM " << loan.calculateOutstandingBalance(payments) << "\n";
    }

    if (!foundAny) {
        cout << "No upcoming payments found for this user.\n";
    }
}

void LoanSystem::viewUsers()
{
    cout << "\n--- View Users ---\n";
    if (users.empty())
    {
        cout << "No users in the system.\n";
        return;
    }

    cout << "Options: (S)ort by Name, (F)ilter/Search by ID/Name/Email, (V)iew All: ";
    char opt;
    cin >> opt;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        opt = 'V';
    }

    LinkedList<User> displayUsers = users;

    if (opt == 'S' || opt == 's')
    {
        SearchNSort::sortUsersByName(displayUsers);
    }
    else if (opt == 'F' || opt == 'f')
    {
        string query;
        cout << "Enter Search Query (ID, Name, or Email): ";
        cin >> ws;
        getline(cin, query);
        displayUsers.clear();
        for (const auto &u : users)
        {
            if (u.getUserId() == query || u.getName().find(query) != string::npos || u.getEmail().find(query) != string::npos)
            {
                displayUsers.push_back(u);
            }
        }
    }

    cout << left << setw(15) << "User ID"
         << setw(20) << "Name"
         << setw(30) << "Email"
         << setw(15) << "Role" << "\n";
    cout << string(80, '-') << "\n";

    for (const auto &user : displayUsers)
    {
        cout << left << setw(15) << user.getUserId()
             << setw(20) << user.getName()
             << setw(30) << user.getEmail()
             << setw(15) << (user.getRole() == Role::ADMIN ? "ADMIN" : "BORROWER") << "\n";
    }
}

void LoanSystem::manageUsers()
{
    cout << "\n--- Manage Users ---\n";
    cout << "1. Add User\n";
    cout << "2. Delete User\n";
    cout << "3. Back\n";
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (choice == 1)
    {
        string name, email, password, roleStr;
        cout << "Name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Email: ";
        getline(cin, email);
        cout << "Password: ";
        getline(cin, password);
        cout << "Role (ADMIN/BORROWER): ";
        getline(cin, roleStr);

        int maxId = 0;
        for (const auto &user : users) {
            string numPart = user.getUserId().substr(1); 
            try {
                int currentId = stoi(numPart);
                if (currentId > maxId)
                    maxId = currentId;
            } catch (...) {}
        }
        int nextU = maxId + 1;
        string newUserId = string("U") + (nextU < 10 ? "00" : (nextU < 100 ? "0" : "")) + to_string(nextU);

        Role role = (roleStr == "ADMIN") ? Role::ADMIN : Role::BORROWER;
        users.push_back(User(newUserId, name, email, password, role));
        FileHandling::saveUsers("data/users.txt", users);
        cout << "Added user with ID: " << newUserId << "\n";
    }
    else if (choice == 2)
    {
        string delId;
        cout << "Enter User ID to delete: ";
        cin >> delId;
        
        int indexToDelete = -1;
        for (int i = 0; i < users.size(); ++i) {
            if (users[i].getUserId() == delId) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete != -1)
        {
            users.remove(indexToDelete);
            FileHandling::saveUsers("data/users.txt", users);
            cout << "Deleted user: " << delId << "\n";
        }
        else
        {
            cout << "User not found.\n";
        }
    }
}

void LoanSystem::viewLoans(const string& filterUserId) {
    cout << "\n--- View Loans ---\n";

    LinkedList<Loan> filteredLoans;

    if (filterUserId.empty()) {
        filteredLoans = loans;
    } else {
        filteredLoans = SearchNSort::filterLoansByUserID(filterUserId, loans);
    }

    if (filteredLoans.empty())
    {
        cout << "No loans in the system.\n";
        return;
    }

    cout << "Options: (S)ort by ID, (F)ilter by UserID, (V)iew All: ";
    char opt;
    cin >> opt;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        opt = 'V';
    }

    LinkedList<Loan> displayLoans = filteredLoans;

    if (opt == 'S' || opt == 's')
    {
        SearchNSort::sortLoansByLoanID(displayLoans);
    }
    else if (opt == 'F' || opt == 'f')
    {
        string uid;
        cout << "Enter User ID: ";
        cin >> uid;
        displayLoans = SearchNSort::filterLoansByUserID(uid, loans);
    }

    cout << left << setw(10) << "Loan ID"
         << setw(10) << "User ID"
         << setw(15) << "Principal"
         << setw(10) << "Rate(%)"
         << setw(10) << "Term(Y)"
         << setw(15) << "Monthly" << "\n";
    cout << string(70, '-') << "\n";

    for (const auto &loan : displayLoans)
    {
        cout << left << setw(10) << loan.getLoanId()
             << setw(10) << loan.getUserId()
             << "RM " << setw(13) << fixed << setprecision(2) << loan.getPrincipal()
             << setw(10) << loan.getInterestRate()
             << setw(10) << loan.getTermYears()
             << "RM " << setw(13) << loan.calculateMonthlyPayment() << "\n";
    }
}

void LoanSystem::loadData() {
    FileHandling::loadUsers("data/users.txt", users);
    FileHandling::loadLoans("data/loans.txt", loans);
    FileHandling::loadPayments("data/payments.txt", payments);

    if (users.empty()) {
        users.push_back(User("U001", "Wei Gang", "weigang@example.com", "pass123", Role::BORROWER));
        users.push_back(User("U002", "Wei Jun", "weijun@example.com", "pass456", Role::ADMIN));
        FileHandling::saveUsers("data/users.txt", users);
    }
}

void LoanSystem::saveData() {
    FileHandling::saveUsers("data/users.txt", users);
    FileHandling::saveLoans("data/loans.txt", loans);
    FileHandling::savePayments("data/payments.txt", payments);
}

LinkedList<Payment> LoanSystem::getPaymentsForLoan(const string& loanId) const
{
    LinkedList<Payment> result;
    for (const auto& p : payments)
    {
        if (p.getLoanId() == loanId)
        {
            result.push_back(p);
        }
    }
    return result;
}

// Payment Queue Methods

void LoanSystem::enqueuePayment(const Payment& payment)
{
    paymentQueue.enqueue(payment);
    cout << "[Queue] Payment " << payment.getPaymentId()
         << " for Loan " << payment.getLoanId()
         << " has been enqueued.\n";
}

void LoanSystem::displayPendingPayments() const
{
    if (paymentQueue.isEmpty())
    {
        cout << "\n[Queue] No pending payments in the queue.\n";
        return;
    }

    cout << "\n[Queue] Pending payments (" << paymentQueue.size() << " total):\n";
    cout << left << setw(10) << "Payment" << setw(10) << "Loan" << setw(15) << "Amount" << setw(15) << "Date" << "\n";
    cout << string(50, '-') << "\n";

    try {
        const LinkedList<Payment>& list = paymentQueue.getList();
        for (const auto& p : list)
        {
            cout << left << setw(10) << p.getPaymentId()
                 << setw(10) << p.getLoanId()
                 << "RM " << setw(12) << fixed << setprecision(2) << p.getAmount()
                 << setw(15) << p.getPaymentDate() << "\n";
        }
    }
    catch (const exception&)
    {
        cout << "Error reading queue.\n";
    }
}

void LoanSystem::processNextPayment()
{
    if (paymentQueue.isEmpty())
    {
        cout << "\n[Queue] No pending payments to process.\n";
        return;
    }

    try {
        while(true)
        {
            Payment pending = paymentQueue.getFront();

            cout << "\n[Queue] Next pending payment:" << endl;
            cout << "  PaymentID: " << pending.getPaymentId() << endl;
            cout << "  LoanID   : " << pending.getLoanId()   << endl;
            cout << "  Amount   : RM " << fixed << setprecision(2) << pending.getAmount() << endl;
            cout << "  Date     : " << pending.getPaymentDate() << endl;

            char decision;
            cout << "\nApprove this payment? (Y/N): ";
            cin >> decision;

            paymentQueue.dequeue(pending);

            if (decision == 'Y' || decision == 'y')
            {
                payments.push_back(pending);
                FileHandling::savePayments("data/payments.txt", payments);

                cout << "\n[Queue] APPROVED Payment " << pending.getPaymentId()
                     << " for Loan " << pending.getLoanId()
                     << ", Amount: RM " << fixed << setprecision(2) << pending.getAmount() << endl;

                for (auto &loan : loans)
                {
                    if (loan.getLoanId() == pending.getLoanId())
                    {
                        LinkedList<Payment> loanPayments = getPaymentsForLoan(loan.getLoanId());
                        double newOutstanding = loan.calculateOutstandingBalance(loanPayments);

                        cout << "[Queue] New outstanding balance for Loan "
                             << loan.getLoanId()
                             << " = RM " << fixed << setprecision(2) << newOutstanding << '\n';
                        break;
                    }
                }
            }
            else
            {
                cout << "\n[Queue] REJECTED Payment " << pending.getPaymentId()
                     << " for Loan " << pending.getLoanId()
                     << ". It was removed from the queue and not recorded." << endl;
            }

            if (paymentQueue.isEmpty())
            {
                cout << "No more pending payments.\n";
                break;
            }

            cout << "\nProcess next payment? (Y/N): ";
            cin >> decision;
            if (decision != 'Y' && decision != 'y')
            {
                break;
            }
        }
    }
    catch (const exception& e)
    {
        cout << "Error processing payment: " << e.what() << endl;
    }
}



// Main Menu Loop

void LoanSystem::menuLoop()
{
    int choice;

    loadData();

    while (true)
    {
        Menu::displayMainMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1)
        {
            string userId, password;
            cout << "\nEnter User ID: ";
            cin >> userId;
            cout << "Enter Password: ";
            cin >> password;

            User *loggedInUser = login(userId, password);

            if (loggedInUser == nullptr)
            {
                cout << "\nInvalid credentials!\n";
                continue;
            }

            cout << "\nWelcome, " << loggedInUser->getName() << "!\n";

            // Loop for User Menu
            if (loggedInUser->getRole() == Role::BORROWER)
            {
                while (true)
                {
                    Menu::displayBorrowerMenu();
                    if (!(cin >> choice))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\n";
                        continue;
                    }

                    if (choice == 1)
                    {
                        viewLoans(loggedInUser->getUserId());
                    }
                    else if (choice == 2)
                    {
                        makePayment(loggedInUser);
                    }
                    else if (choice == 3)
                    {
                        viewPaymentHistory(loggedInUser->getUserId());
                    }
                    else if (choice == 4)
                    {
                        viewUpcomingPayments(loggedInUser->getUserId());
                    }
                    else if (choice == 5)
                    {
                        createLoan(loggedInUser);
                    }
                    else if (choice == 6)
                    {
                        cout << "\nLogging out...\n";
                        break;
                    }
                    else
                    {
                        cout << "\nInvalid choice!\n";
                    }
                }
            }
            else
            {
                // ADMIN
                while (true)
                {
                    Menu::displayAdminMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1)
        {
            viewLoans("");
        }
        else if (choice == 2)
        {
            viewUsers();
        }
        else if (choice == 3)
        {
            viewPaymentHistory("");
        }
        else if (choice == 4)
        {
            createLoan(loggedInUser);
        }
        else if (choice == 5)
        {
            manageUsers();
        }
        else if (choice == 6)
        {
            displayPendingPayments();
        }
        else if (choice == 7)
        {
            displayPendingLoans();
        }
        else if (choice == 8)
        {
            processNextPayment();
        }
        else if (choice == 9)
        {
            processLoanRequests();
        }
        else if (choice == 10)
        {
            cout << "\nLogging out...\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
                }
            }
        }
        else if (choice == 2)
        {
            cout << "\nThank you for using the Loan Management System!\n";
            saveData();
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}

void LoanSystem::processLoanRequests()
{
    if (loanRequests.isEmpty()) {
        cout << "\n[Queue] No pending loan requests." << endl;
        return;
    }

    try {
        while (true)
        {
            Loan request = loanRequests.getFront();
            cout << "\n--- Processing Loan Request ---" << endl;
            cout << "Loan ID: " << request.getLoanId() << " (Provisional)" << endl;
            cout << "User ID: " << request.getUserId() << endl;
            cout << "Amount : RM " << request.getPrincipal() << endl;
            cout << "Term   : " << request.getTermYears() << " years" << endl;
            cout << "Date   : " << request.getDate() << endl;

            cout << "\nApprove this loan? (Y/N): ";
            char choice;
            cin >> choice;

            // Remove from queue
            Loan temp(0,0,0,"","","");
            loanRequests.dequeue(temp); 

            if (choice == 'Y' || choice == 'y') {
                loans.push_back(request);
                FileHandling::saveLoans("data/loans.txt", loans);
                cout << "Loan APPROVED and active.\n";
            } else {
                cout << "Loan REJECTED and discarded.\n";
            }

            if (loanRequests.isEmpty())
            {
                cout << "No more pending loan requests.\n";
                break;
            }

            cout << "\nProcess next loan request? (Y/N): ";
            cin >> choice;
            if (choice != 'Y' && choice != 'y')
            {
                break;
            }
        }

    } catch (const exception& e) {
        cout << "Error " << e.what() << endl;
    }
}

void LoanSystem::displayPendingLoans() const {
    if (loanRequests.isEmpty()) {
        cout << "\n[Queue] No pending loan requests.\n";
        return;
    }

    cout << "\n[Queue] Pending Loan Requests (" << loanRequests.size() << " total):\n";
    cout << left << setw(10) << "Loan" << setw(10) << "User" << setw(15) << "Amount" << setw(15) << "Date" << "\n";
    cout << string(50, '-') << "\n";

    const LinkedList<Loan>& list = loanRequests.getList();
    for (const auto& l : list)
    {
         cout << left << setw(10) << l.getLoanId()
         << setw(10) << l.getUserId()
         << "RM " << setw(12) << fixed << setprecision(2) << l.getPrincipal()
         << setw(15) << l.getDate() << "\n";
    }
}

void LoanSystem::createLoan(User* currentUser)
{
    cout << "\n--- New Loan Application ---\n";
    
    string targetUserId;
    if (currentUser->getRole() == Role::ADMIN) 
    {
        cout << "Enter User ID (Borrower): ";
        cin >> targetUserId;

        bool found = false;
        for (const auto& u : users) {
             if (u.getUserId() == targetUserId) {
                 found = true;
                 break;
             }
        }
        if (!found) {
            cout << "User not found.\n";
            return;
        }
    }
    else 
    {
        targetUserId = currentUser->getUserId();
    }
    
    int maxId = 0;
    
    for (const auto &loan : loans) {
        string numPart = loan.getLoanId().substr(1);
        try {
            int val = stoi(numPart);
            if (val > maxId) maxId = val;
        } catch (...) {}
    }
    
    const LinkedList<Loan>& pendingList = loanRequests.getList();
    for (const auto &loan : pendingList) {
        string numPart = loan.getLoanId().substr(1);
        try {
            int val = stoi(numPart);
            if (val > maxId) maxId = val;
        } catch (...) {}
    }
    
    int next = maxId + 1;
    string loanId = string("L") + (next < 10 ? "00" : (next < 100 ? "0" : "")) + to_string(next);

    double principal, interestRate;
    int termYears;

    cout << "Loan ID (generated): " << loanId << "\n";
    cout << "Enter Principal Amount: RM ";
    cin >> principal;
    cout << "Enter Interest Rate (pa %): ";
    cin >> interestRate;
    cout << "Enter Loan Term (years): ";
    cin >> termYears;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    sprintf(buffer, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    string date = string(buffer);

    Loan newLoan(principal, interestRate, termYears, targetUserId, loanId, date);

    if (currentUser->getRole() == Role::ADMIN)
    {
        cout << "\nApprove immediately? (Y/N): ";
        char ans;
        cin >> ans;
        if (ans == 'Y' || ans == 'y') {
            loans.push_back(newLoan);
            FileHandling::saveLoans("data/loans.txt", loans);
            cout << "Loan Created and Active.\n";
        } else {
            loanRequests.enqueue(newLoan);
            cout << "Loan added to pending queue.\n";
        }
    }
    else
    {
        loanRequests.enqueue(newLoan);
        cout << "Loan Request Submitted (Pending Approval).\n";
    }
}
