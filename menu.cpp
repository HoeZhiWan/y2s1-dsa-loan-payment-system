#include "menu.h"
#include <iostream>

using namespace std;

void Menu::displayMainMenu() {
    cout << "\n=================================\n";
    cout << "   Loan Management System\n";
    cout << "=================================\n";
    cout << "1. Login\n";
    cout << "2. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}

void Menu::displayBorrowerMenu() {
    cout << "\n=================================\n";
    cout << "      Borrower Menu\n";
    cout << "=================================\n";
    cout << "1. View My Loans\n";
    cout << "2. Make Payment\n";
    cout << "3. View Payment History\n";
    cout << "4. Logout\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}

void Menu::displayAdminMenu() {
    cout << "\n=================================\n";
    cout << "       Admin Menu\n";
    cout << "=================================\n";
    cout << "1. View All Loans\n";
    cout << "2. View/Search/Sort Users\n";
    cout << "3. View/Search/Sort Payments\n";
    cout << "4. Create New Loan\n";
    cout << "5. Manage Users\n";
    cout << "6. Logout\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}
