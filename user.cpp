#include "user.h"

using namespace std;

User::User(string userId, string name, string email, string passwordHash, Role role)
    : userId(userId), name(name), email(email), passwordHash(passwordHash), role(role)
{
}

string User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}

string User::getPasswordHash() const {
    return passwordHash;
}

string User::getRole() const {
    if (role == Role::ADMIN) {
        return "ADMIN";
    }
    return "BORROWER";
}

void User::setName(const string& name) {
    this->name = name;
}

void User::setEmail(const string& email) {
    this->email = email;
}

void User::setPasswordHash(const string& passwordHash) {
    this->passwordHash = passwordHash;
}

void User::setRole(const string& role) {
    if (role == "ADMIN") {
        this->role = Role::ADMIN;
    } else {
        this->role = Role::BORROWER;
    }
}
