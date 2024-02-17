#include "user.h"
#include "valid.h"

#include <iostream>
#include <string>
#include <fstream>


std::string path = "users/";

bool search_user(std::string* login)
{
    std::ifstream exist;
    exist.open(path + *login + ".txt");
    
    if (exist) // If file exist
    {   
        exist.close();
        return 1;
    }
    else
    {
        exist.close();
        return 0;
    }
}


void User::load_user(std::string* login)
{
    std::ifstream load;
    load.open(path + *login + ".txt");
    if (load.is_open())
    {   
        std::string* data[5] {&this->login, &this->password, &this->name, &this->email, &this->phone};
        std::string line;
        for (int i {}; i < 5; i++)
        {   
            load >> line;
            int index = line.find(":");
            line = line.substr(index+1);
            *data[i] = line;
        }
    }
}
std::string User::password_hash(std::string* password)
{

    return *password;
}


User::User(std::string login, std::string password, std::string name, std::string email="", std::string phone="")
{
    this->login = login;
    this->password = password;
    this->name = name;
    this->email = email;
    this->phone = phone;
    std::cout << "Account has been created" << std::endl;
}
User::User(std::string login)
{
    load_user(&login);
}
void User::save_user() const
{
    std::ofstream save;
    save.open(path+login+".txt");
    if (save.is_open())
    {
        save << "login:" << login << "\n";
        save << "password:"<< password << "\n";
        save << "name:" << name << "\n";
        save << "email:" << email << "\n";
        save << "phone:" << phone;
    }
    save.close();
    std::cout << "Account has been saved" << std::endl;
}
bool User::password_validation(std::string* password)
{   
    std::string hash_password = password_hash(password);
    if (hash_password == this->password )
        return 1;
    else
        return 0;
}
void User::change_name()
{
    std::cout << "Enter new name: ";
    std::cin >> this->name;
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
    }
    else
    {
        std::cout << "Email is not valid. Try again" << std::endl;
    }
}
void User::change_password(std::string* old_password)
{
    std::string hash_old_password = password_hash(old_password);
    if (hash_old_password == this->password)
    {
        std::string new_password {};
        std::cout << "Enter new password: ";
        std::cin >> new_password;
        if (is_valid_password(&new_password))
        {
            this->password = password_hash(&new_password);
            std::cout << "Password change successful" << std::endl;
        }
        else
        {
            std::cout <<
            "The password must consist of uppercase and lowercase letters, numbers and special characters"
            << "\n" << "Try again" << std::endl;
        }
    }
}
void User::change_phone(std::string* phone)
{
    if (is_valid_phone(phone))
        this->phone = *phone;
    else
    {
        std::cout << "Phone number is not valid. Try again" << std::endl;
    }
}

