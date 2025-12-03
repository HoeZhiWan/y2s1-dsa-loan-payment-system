#include "loanSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>

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

void LoanSystem::createLoan()
{
    string loanId, userId;
    double principal, interestRate;
    int termYears;

    cout << "\n--- Create New Loan ---\n";
    int maxId = 0;
    for (const auto &loan : loans)
    {
        string numPart = loan.getLoanId().substr(1);
        try
        {
            int currentId = stoi(numPart);
            if (currentId > maxId)
            {
                maxId = currentId;
            }
        }
        catch (...)
        {
            // Ignore malformed loan IDs
        }
    }
    int next = maxId + 1;
    loanId = string("L") + (next < 10 ? "00" : (next < 100 ? "0" : "")) + to_string(next);
    cout << "Generated Loan ID: " << loanId << "\n";

    cout << "Enter User ID (Borrower): ";
    cin >> userId;

    bool userExists = false;
    for (const auto &user : users)
    {
        if (user.getUserId() == userId)
        {
            userExists = true;
            break;
        }
    }
    if (!userExists)
    {
        cout << "Error: User ID " << userId << " not found. Cannot create loan.\n";
        return;
    }

    cout << "Enter Principal Amount: RM  ";
    cin >> principal;
    cout << "Enter Interest Rate (pa %): ";
    cin >> interestRate;
    cout << "Enter Loan Term (years): ";
    cin >> termYears;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Loan creation failed.\n";
        return;
    }

    Loan newLoan(principal, interestRate, termYears, userId, loanId);
    loans.push_back(newLoan);

    cout << "\nLoan created successfully!\n";
    cout << "Loan ID: " << loanId << "\n";
    cout << "Monthly Payment: RM " << fixed << setprecision(2) << newLoan.calculateMonthlyPayment() << "\n";
    cout << "Total Payment: RM " << newLoan.calculateTotalPayment() << "\n";
    cout << "Total Interest: RM " << newLoan.calculateTotalInterest() << "\n";

    FileHandling::saveLoans("data/loans.txt", loans);
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

    Payment newPayment(amount, date, loanId);
    payments.push_back(newPayment);

    cout << "\nPayment recorded successfully!\n";

    FileHandling::savePayments("data/payments.txt", payments);
}

void LoanSystem::viewPaymentHistory(const string &filterUserId)
{
    cout << "\n--- Payment History ---\n";
    vector<Payment> filteredPayments;

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

void LoanSystem::administerUsers()
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

    vector<User> displayUsers = users;

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
            string numPart = user.getUserId().substr(1); // Remove 'U'
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
        auto it = remove_if(users.begin(), users.end(), [&](const User &u)
                            { return u.getUserId() == delId; });
        if (it != users.end())
        {
            users.erase(it, users.end());
            FileHandling::saveUsers("data/users.txt", users);
            cout << "Deleted user: " << delId << "\n";
        }
        else
        {
            cout << "User not found.\n";
        }
    }
}

void LoanSystem::menuLoop()
{
    int choice;

    FileHandling::loadUsers("data/users.txt", users);
    FileHandling::loadLoans("data/loans.txt", loans);
    FileHandling::loadPayments("data/payments.txt", payments);

    if (users.empty())
    {
        users.push_back(User("U001", "Wei Gang", "weigang@example.com", "pass123", Role::BORROWER));
        users.push_back(User("U002", "Wei Jun", "weijun@example.com", "pass456", Role::ADMIN));
        FileHandling::saveUsers("data/users.txt", users);
    }

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
                        cout << "\n--- My Loans ---\n";
                        vector<Loan> myLoans = SearchNSort::filterLoansByUserID(loggedInUser->getUserId(), loans);

                        if (myLoans.empty())
                        {
                            cout << "No loans found.\n";
                        }
                        else
                        {
                            cout << left << setw(10) << "Loan ID"
                                 << setw(15) << "Principal"
                                 << setw(10) << "Rate(%)"
                                 << setw(10) << "Term(Y)"
                                 << setw(15) << "Monthly"
                                 << setw(15) << "Balance" << "\n";
                            cout << string(75, '-') << "\n";

                            for (const auto &loan : myLoans)
                            {
                                cout << left << setw(10) << loan.getLoanId()
                                     << "RM " << setw(13) << fixed << setprecision(2) << loan.getPrincipal()
                                     << setw(10) << loan.getInterestRate()
                                     << setw(10) << loan.getTermYears()
                                     << "RM " << setw(13) << loan.calculateMonthlyPayment()
                                     << "RM " << loan.calculateOutstandingBalance(payments) << "\n";
                            }
                        }
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
                        cout << "\n--- All Loans ---\n";
                        if (loans.empty())
                        {
                            cout << "No loans in the system.\n";
                        }
                        else
                        {
                            cout << "Options: (S)ort by ID, (F)ilter by UserID, (V)iew All: ";
                            char opt;
                            cin >> opt;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                opt = 'V';
                            }

                            vector<Loan> displayLoans = loans;

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
                                     << "RM " << loan.calculateMonthlyPayment() << "\n";
                            }
                        }
                    }
                    else if (choice == 2)
                    {
                        administerUsers();
                    }
                    else if (choice == 3)
                    {
                        viewPaymentHistory("");
                    }
                    else if (choice == 4)
                    {
                        createLoan();
                    }
                    else if (choice == 5)
                    {
                        manageUsers();
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
        }
        else if (choice == 2)
        {
            cout << "\nThank you for using the Loan Management System!\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}
