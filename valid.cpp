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
    static const std::regex pattern(R"(^[a-z]{3,}@[a-z]{2,}\.[a-z]{2,4}$)");
    return std::regex_match(*email, pattern);
}
bool is_valid_phone(std::string* phone)
{
    static const std::regex pattern(R"(^[\+]?\d{11}$)");
    return std::regex_match(*phone, pattern);
}
