#include "valid.h"

#include <string>
#include <regex>
#include <fstream>
#include <filesystem>

bool is_valid_username(std::string* username)
{
    if (!std::filesystem::exists("usernames.txt"))
            return 1;
    else
    {
        std::ifstream users;
        std::string line;
        users.open("usernames.txt");
        while (users)
        {
            std::getline(users, line);
            if (line == *username)
            {
                users.close();
                return 0;
            }
        }
        users.close();
        return 1;
    }
}

bool is_valid_password(std::string* password)
{
    static const std::regex pattern(R"(^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,}$)");
    return std::regex_match(*password, pattern);
}

bool is_valid_email(std::string* email)
{
    static const std::regex pattern(R"(^([a-zA-Z0-9._-]+@[a-zA-Z]+\.[a-z]+)$)");
    return std::regex_match(*email, pattern);
}
bool is_valid_phone(std::string* phone)
{
    static const std::regex pattern(R"(^[\+]?\d{11}$)");
    return std::regex_match(*phone, pattern);
}
