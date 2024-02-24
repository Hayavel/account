#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"

#include "const.h"
#include "valid.h"

#include <iostream>
#include <string>
#include <fstream>


#ifndef USER_H
#define USER_H


class User
{
private:
    std::string login;
    std::string password;

    std::string username;
    std::string email;
    std::string phone;

    void load_user(std::string*);
    std::string password_hash(std::string*);
public:
    User(std::string login, std::string password, std::string username, std::string email, std::string phone);
    User(std::string login);

    void save_user() const;
    void save_username() const;
    bool delete_user() const;
    void delete_username() const;
    bool password_validation(std::string*);
    void change_username();
    void change_email();
    void change_password(std::string*);
    void change_phone();
    std::string get_username();
    std::string get_email();
    std::string get_phone();
};

#endif