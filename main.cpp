#include "valid.h"
#include "user.h"

#include <iostream>
#include <string>

/*
!!Шифрование пароля                                         -
Создание нового пользователя                                - сделано
RegEx для пароля, почты, телефона, логина                   - сделано
Проверка существует ли пользователь при создании            - сделано
Возврат данных запрошенного существуещего пользователя      -
Функция смены пароля                                        - сделано
Функция смены имени                                         - сделано
Функция смены контактных данных (почта, телефон)            - сделано
Вход в личный кабинет                                       - сделано


Какой-то фукнционал с аккаунтом                             -
Попробовать переделать через ссылки и указатели             -
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


        std::cout << "* - required to fill out" << std::endl;
        do
        {
            std::cout << "*Enter login: ";
            std::cin >> login;
            if (search_user(login))
                std::cout << "User exist" << std::endl;
        }
        while (search_user(login) && login=="");

        std::cout << "*Enter name: ";
        std::cin >> name;
        do
        {
            std::cout << "Enter email: ";
            std::cin >> email;
        }
        while (is_valid_email(email));
        do
        {
            std::cout << "Enter phone: ";
            std::cin >> phone;
        }
        while (is_valid_phone(phone));
        do
        {
            std::cout << "*Enter password: ";
            std::cin >> password;
        }
        while (is_valid_password(password));

        User new_user {login, password, name, email, phone};
        new_user.save_user();
    }
    else if (choice == "Login")
    {
        do
        {
            std::cout << "Enter login: ";
            std::cin >> login;
            if (!search_user(login))
                    std::cout << "User does not exist" << std::endl;
        }
        while (!search_user(login));
        User active_user {login};
        
        do
        {
            std::cout << "Enter password: ";
            std::cin >> password;
            if (!active_user.password_validation(password))
                std::cout << "Wrong password" << std::endl;
        }
        while (!active_user.password_validation(password));
        std::cout << "Login successful" << std::endl;
    }
}