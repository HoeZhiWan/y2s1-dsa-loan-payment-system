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
    string passwordHash;    // Hashed password for security
    Role role;              // Role of the user (borrower, admin)

public:
    User(string userId, string name, string email, string passwordHash, Role role);

    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPasswordHash() const;
    string getRole() const;

    void setName(const string& name);
    void setEmail(const string& email);
    void setPasswordHash(const string& passwordHash);
    void setRole(const string& role);
};

#endif