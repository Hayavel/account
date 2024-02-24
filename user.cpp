#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"

#include "const.h"
#include "user.h"
#include "valid.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


void User::load_user(std::string* login)
{
    std::ifstream load;
    load.open(users_path + *login + ".txt");
    if (load.is_open())
    {   
        std::string* data[5] {&this->login, &this->password, &this->username, &this->email, &this->phone};
        std::string line;
        for (int i {}; i < 5; i++)
        {   
            load >> line;
            int index = line.find(":");
            line = line.substr(index+1);
            *data[i] = line;
        }
    }
    load.close();
}

std::string User::password_hash(std::string* password)
{
    std::string pw = *password;
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA1::DIGESTSIZE];
    hash.CalculateDigest(digest, (const CryptoPP::byte*)pw.c_str(), pw.size());
    std::string output;
    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink test = CryptoPP::StringSink(output);
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    return output;
}


User::User(std::string login, std::string password, std::string username, std::string email="", std::string phone="")
{
    this->login = login;
    this->password = password_hash(&password);
    this->username = username;
    this->email = email;
    this->phone = phone;
    std::cout << "Account has been created" << std::endl;
    save_user();
    save_username();
}

User::User(std::string login)
{
    load_user(&login);
}

void User::save_user() const
{
    std::ofstream save;
    save.open(users_path+login+".txt");
    if (save.is_open())
    {
        save << "login:" << login << "\n";
        save << "password:"<< password << "\n";
        save << "username:" << username << "\n";
        save << "email:" << email << "\n";
        save << "phone:" << phone;
    }
    save.close();
    std::cout << "Account has been saved" << std::endl;
}

void User::save_username() const
{
    std::ofstream save;
    save.open("usernames.txt", std::ios::app);
    if (save.is_open())
        save << username << std::endl;
    save.close();
}

bool User::delete_user() const
{
    std::string answer {};
    std::cout << "Are you sure you want to delete your account?[Y/n]: ";
    std::cin >> answer;
    if (answer == "Y")
    {
        delete_username();
        std::remove((users_path+login+".txt").c_str());
        std::cout << "Account has been deleted" << std::endl;
        return 1;
    }
    else
        return 0;    
}

void User::delete_username() const
{
    std::fstream users;
    std::vector<std::string> usernames;
    std::string line;
    users.open(usernames_path, std::ios::in);
    while (users)
    {
        std::getline(users, line);
        usernames.push_back(line);
    }
    users.close();
    users.open(usernames_path, std::ios::out);
    for (int i {}; i < usernames.size()-1; i++)
    {
        if (usernames[i] != username)
            users << usernames[i] << std::endl;
    }
    users.close();
}

bool User::password_validation(std::string* password)
{   
    std::string hash_password = password_hash(password);
    if (hash_password == this->password )
        return 1;
    else
        return 0;
}

void User::change_username()
{
    std::string new_username {};
    std::cout << "Enter new username: ";
    std::cin >> new_username;
    if (new_username != "" && is_valid_username(&new_username))
    {
        delete_username();
        this->username = new_username;
        save_user();
        save_username();   
        std::cout << "Username change successful" << std::endl;
    }
    else
    {
        if (new_username == "")
            std::cout << "Username is not valid" << std::endl;
        else
            std::cout << "Username has already been taken" << std::endl;
    }
}

void User::change_email()
{
    std::string new_email {};
    std::cout << "Enter new email: ";
    std::cin >> new_email;
    if (is_valid_email(&new_email))
    {
        this->email = new_email;
        std::cout << "Email change successful" << std::endl;
        save_user();
    }
    else
    {
        std::cout << "Email is not valid. Try again" << std::endl;
    }
}

void User::change_password()
{
    std::string old_password {};
    std::cout << "Enter old password: ";
    std::cin >> old_password;
    std::string hash_old_password = password_hash(&old_password);
    if (hash_old_password == this->password)
    {
        std::string new_password {};
        std::cout << "Enter new password: ";
        std::cin >> new_password;
        if (is_valid_password(&new_password))
        {
            this->password = password_hash(&new_password);
            std::cout << "Password change successful" << std::endl;
            save_user();
        }
        else
        {
            std::cout <<
            "The password must consist of uppercase and lowercase letters, numbers and special characters"
            << "\n" << "Try again" << std::endl;
        }
    }
}

void User::change_phone()
{
    std::string phone {};
    std::cout << "Enter new phone number: ";
    std::cin >> phone;
    if (is_valid_phone(&phone))
    {
        this->phone = phone;
        std::cout << "Phone number change successful" << std::endl;
        save_user();
    }
    else
    {
        std::cout << "Phone number is not valid. Try again" << std::endl;
    }
}

std::string User::get_username()
{
    return username;
}
std::string User::get_email()
{
    return email;
}
std::string User::get_phone()
{
    return phone;
}
