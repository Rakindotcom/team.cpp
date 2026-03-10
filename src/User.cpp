#pragma once
#include <string>
#include <iostream>

namespace GarmentFactory {

class User {
private:
    std::string userId;
    std::string username;
    std::string password;
    std::string role; // "Admin", "Supervisor", "QualityManager", etc.
    std::string email;
    std::string lastLogin; // Simple string date for now

public:
    User() {}
    User(std::string id, std::string user, std::string pass, std::string r, std::string mail)
        : userId(id), username(user), password(pass), role(r), email(mail) {}

    bool login(std::string inputUser, std::string inputPass) {
        return (username == inputUser && password == inputPass);
    }

    bool logout() {
        return true;
    }

    void updateProfile(std::string newEmail) {
        email = newEmail;
    }

    // Getters
    std::string getUsername() const { return username; }
    std::string getRole() const { return role; }
};

} // namespace GarmentFactory
