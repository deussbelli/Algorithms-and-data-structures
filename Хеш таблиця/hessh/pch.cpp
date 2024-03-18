//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <map>
#include <windows.h>
#include <string>

using namespace std;

class HashTable {
    map<string, string> table;

public:
    void add(string password, string username) {
        table[password] = username;
    }

    string findUserByPassword(string password) {
        map<string, string>::iterator it = table.find(password);
        if (it != table.end()) {
            return it->second;
        }
        return "Коритувача з таким паролем не знайдено.";
    }

    string findPasswordByUsername(string username) {
        for (const auto& pair : table) {
            if (pair.second == username) {
                return pair.first;
            }
        }
        return "Уведенего паролю не знайдено у базі даних.";
    }

    void remove(string password, string username) {
        map<string, string>::iterator it = table.find(password);
        if (it != table.end() && it->second == username) {
            table.erase(it);
        }
    }

    void replacePassword(string oldPassword, string newPassword) {
        map<string, string>::iterator it = table.find(oldPassword);
        if (it != table.end()) {
            table[newPassword] = it->second;
            table.erase(it);
        }
    }

    void replaceUsername(string password, string newUsername) {
        map<string, string>::iterator it = table.find(password);
        if (it != table.end()) {
            it->second = newUsername;
        }
    }

    void remove(string password) {
        table.erase(password);
    }

    void display() {
        cout << "[ Пароль ]\t[ Ім'я користувача ]" << endl;
        for (auto it = table.begin(); it != table.end(); ++it) {
            cout << it->first << "\t" << "\t" << it->second << endl;
        }
    }
};

int test() {
    HashTable users;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Добавление элементов
    users.add("pass1", "user1");
    users.add("pass2", "user2");
    users.add("pass3", "user3");

    users.display();

    int choice;

    do {
        cout << "\nОберіть дію: \n"
            << "[1] - Знайти користувача [за паролем]; \n"
            << "[2] - Знайти пароль [для користувача]; \n"
            << "[3] - Замінити значення [пароль]; \n"
            << "[4] - Замінити значення [ім'я користувача]; \n"
            << "[5] - Додати елемент до таблиці [УВАГА: паролі не мають співпадати]; \n"
            << "[6] - Видалити користувача [за паролем]; \n"
            << "[7] - Видалити користувача [за паролем та ім'ям]; \n"
            << "[8] - Показати таблицю;\n"
            << "[0] - Завершити роботу програми." << endl;
        cin >> choice;

        string password;
        string username;
        string new_password;
        string new_username;

        switch (choice) {
        case 1:
        {
            cout << "Уведіть пароль: "; cin >> password;
            cout << "Користувач з таким паролем: " << users.findUserByPassword(password) << endl;
            break;
        }
        case 2:
        {
            cout << "Уведіть ім'я користувача: "; cin >> username;
            cout << "Пароль користувача: " << users.findPasswordByUsername(username) << endl;
            break;
        }
        case 3:
        {
            cout << "Уведіть пароль, який потрібно замінити: "; cin >> password;
            cout << "Уведіть новий пароль: "; cin >> new_password;
            users.replacePassword(password, new_password);

            users.display();
            break;
        }
        case 4:
        {
            cout << "Уведіть ім'я користувача: "; cin >> username;
            cout << "Уведіть пароль користувача: "; cin >> password;
            cout << "Уведіть нове ім'я: "; cin >> new_username;
            users.replaceUsername(password, new_username);

            users.display();
            break;
        }
        case 5:
        {
            cout << "Уведіть нове ім'я: "; cin >> new_username;
            cout << "Уведіть пароль для цього користувача: "; cin >> new_password;
            users.add(new_password, new_username);

            users.display();
            break;
        }
        case 6:
        {
            cout << "Уведіть пароль користувача, якого треба видалити: "; cin >> password;
            users.remove(password);

            users.display();
            break;
        }
        case 7:
        {
            cout << "Уведіть ім'я користувача: "; cin >> username;
            cout << "Уведіть пароль: "; cin >> password;
            users.remove(password, username);

            users.display();
            break;
        }
        case 8:
        {
            users.display();
            break;
        }
        case 0:
            break;
        default:
            cout << "[ ERROR ]. Обранної дії немає у списку. Спробуйте ще раз." << endl << endl;
        }
    } while (choice != 0);

    return 0;
}

