#include "const.h"

#include <string>
#include <regex>
#include <fstream>
#include <filesystem>

#ifndef VALID_H
#define VALID_H

bool is_valid_username(std::string*);
bool is_valid_password(std::string*);
bool is_valid_email(std::string*);
bool is_valid_phone(std::string*);

bool search_user(std::string*);

#endif