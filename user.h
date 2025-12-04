#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum class Role {
    BORROWER,
    ADMIN
};

class User
{
private:
    string userId;          // Unique ID for the user
    string name;            // Name of the user
    string email;           // Email address of the user
    string password;        // Password for security
    Role role;              // Role of the user (borrower, admin)

public:
    User(string userId, string name, string email, string password, Role role);

    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    Role getRole() const;

    void setName(const string& name);
    void setEmail(const string& email);
    void setPassword(const string& password);
    void setRole(const string& role);
};

#endif