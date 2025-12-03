# Loan Management System

## Overview
Simple console loan management demo: user authentication, loan creation (admin only), payments, and file persistence.

## Features

### Borrowers
- View personal loans
- Make payments
- View personal payment history (filter + sort)

### Admins
- Create loans for borrowers
- View / search / sort all loans, users and payments
- Manage users (add / delete)

## Algorithms

### Linear Search 
- Filtering loans by **User ID**, **Interest Rate**, **Principal**, **Outstanding Balance**, **Term Years**, and **Date Range**.
- Searching payments by **Loan ID** and **Date**.
- Filtering payments by **Amount Range** and by **User ID**.
- Searching users by **Email** and filtering users by **Role**.

### Binary Search
- Searching for a loan by **Loan ID**.
- Searching for a user by **User ID**.

### QuickSort
- Sorting loans by **Principal**, **Interest Rate**, **Outstanding Balance**, **Term Years**, **Loan Date**, **Loan ID**, and **User ID**.
- Sorting payments by **Payment ID**, **Loan ID**, **Date**, and **Amount**.
- Sorting users by **Name**, **Role**, **Email**, and **User ID**.

## Run

```powershell
.\loanSystem.exe
```

## Test Login
- Login as borrower `U001` (`pass123`) and view your loans/payments
- Login as admin `U002` (`pass123`) to create loans

