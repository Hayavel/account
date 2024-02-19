#include "valid.h"
#include "user.h"

#include <iostream>
#include <string>

/*
!!Шифрование пароля                                         - сделано
Создание нового пользователя                                - сделано
RegEx для пароля, почты, телефона, логина                   - сделано
Проверка существует ли пользователь при создании            - сделано
Возврат данных запрошенного существуещего пользователя      - сделано
Функция смены пароля                                        - сделано
Функция смены имени                                         - сделано
Функция смены контактных данных (почта, телефон)            - сделано
Вход в личный кабинет                                       - сделано
Удаление аккаунта                                           - сделано


Какой-то фукнционал с аккаунтом                             - 
Попробовать переделать через ссылки и указатели             - сделано
*/


int main()
{
    std::string choice {};

    std::string login {""};
    std::string password {""};

    std::cout << "Register or Login: ";
    std::cin >> choice;

    if (choice == "Register")
    {       
        std::string name {""};
        std::string email {""};
        std::string phone {""};


        std::cout << "\t* - required to fill out" << std::endl;
        do
        {
            std::cout << "*Enter login: ";
            std::cin >> login;
            if (search_user(&login))
                std::cout << "User exist" << std::endl;
        }
        while (search_user(&login) || login=="");

        std::cout << "*Enter name: ";
        std::cin >> name;
        do
        {
            std::cout << "Enter email: ";
            std::cin >> email;
        }
        while (!is_valid_email(&email));
        do
        {
            std::cout << "Enter phone: ";
            std::cin >> phone;
        }
        while (!is_valid_phone(&phone));
        do
        {
            std::cout << "*Enter password: ";
            std::cin >> password;
        }
        while (!is_valid_password(&password));

        User new_user {login, password, name, email, phone};
        new_user.save_user();
    }
    else if (choice == "Login")
    {
        do
        {
            std::cout << "Enter login: ";
            std::cin >> login;
            if (!search_user(&login))
                    std::cout << "User does not exist" << std::endl;
        }
        while (!search_user(&login));
        User active_user {login};
        
        do
        {
            std::cout << "Enter password: ";
            std::cin >> password;
            if (!active_user.password_validation(&password))
                std::cout << "Wrong password" << std::endl;
        }
        while (!active_user.password_validation(&password));
        std::cout << "Login successful" << std::endl;
        std::string action;
        while (true)
        {
            std::cout << "\nSettings[quit]:" << "\t" << "Actions:" << "\n"; 
            std::cout << "- change name" << "\t" << "- get name" << "\n"; 
            std::cout << "- change email" << "\t" << "- get email" << "\n";
            std::cout << "- change phone" << "\t" << "- get phone" << "\n";
            std::cout << "- change password" << "\t" << "- get something" << "\n";
            std::cout << "- !delete account" << std::endl; 
            std::cout << "Enter: "; 
            std::getline(std::cin>>std::ws, action);
            if (action == "change name")
                active_user.change_name();
            else if (action == "change email")
                active_user.change_email();
            else if (action == "change phone")
                active_user.change_phone();
            else if (action == "change password")
            {   
                std::string old_password {};
                std::cout << "Enter old password: ";
                std::cin >> old_password;
                active_user.change_password(&old_password);
            }
            else if(action == "!delete account")
            {
                if (active_user.delete_user())
                    break;
            }
            else if(action == "get name")
            {
                std::cout << "\nYour name: " << active_user.get_name() << std::endl;

            }
            else if(action == "get email")
            {
                std::cout << "\nYour email: " << active_user.get_email() << std::endl;

            }
            else if(action == "get phone")
            {
                std::cout << "\nYour phone: " << active_user.get_phone() << std::endl;
                
            }
            else if (action == "quit")
                break;
            else
            {
                std::cout << "\nSomething wrong" << std::endl;
            }

        }
    }
}