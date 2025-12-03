#include "user.h"

using namespace std;

User::User(string userId, string name, string email, string password, Role role)
    : userId(userId), name(name), email(email), password(password), role(role)
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

string User::getPassword() const {
    return password;
}

Role User::getRole() const {
    if (role == Role::ADMIN) {
        return Role::ADMIN;
    }
    return Role::BORROWER;
}

void User::setName(const string& name) {
    this->name = name;
}

void User::setEmail(const string& email) {
    this->email = email;
}

void User::setPassword(const string& password) {
    this->password = password;
}

void User::setRole(const string& role) {
    if (role == "ADMIN") {
        this->role = Role::ADMIN;
    } else {
        this->role = Role::BORROWER;
    }
}
