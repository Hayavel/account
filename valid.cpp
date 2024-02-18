#include "valid.h"

#include <string>
#include <regex>


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
