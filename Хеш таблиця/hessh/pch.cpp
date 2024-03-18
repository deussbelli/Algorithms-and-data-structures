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
        return "���������� � ����� ������� �� ��������.";
    }

    string findPasswordByUsername(string username) {
        for (const auto& pair : table) {
            if (pair.second == username) {
                return pair.first;
            }
        }
        return "��������� ������ �� �������� � ��� �����.";
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
        cout << "[ ������ ]\t[ ��'� ����������� ]" << endl;
        for (auto it = table.begin(); it != table.end(); ++it) {
            cout << it->first << "\t" << "\t" << it->second << endl;
        }
    }
};

int test() {
    HashTable users;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ���������� ���������
    users.add("pass1", "user1");
    users.add("pass2", "user2");
    users.add("pass3", "user3");

    users.display();

    int choice;

    do {
        cout << "\n������ ��: \n"
            << "[1] - ������ ����������� [�� �������]; \n"
            << "[2] - ������ ������ [��� �����������]; \n"
            << "[3] - ������� �������� [������]; \n"
            << "[4] - ������� �������� [��'� �����������]; \n"
            << "[5] - ������ ������� �� ������� [�����: ����� �� ����� ���������]; \n"
            << "[6] - �������� ����������� [�� �������]; \n"
            << "[7] - �������� ����������� [�� ������� �� ��'��]; \n"
            << "[8] - �������� �������;\n"
            << "[0] - ��������� ������ ��������." << endl;
        cin >> choice;

        string password;
        string username;
        string new_password;
        string new_username;

        switch (choice) {
        case 1:
        {
            cout << "������ ������: "; cin >> password;
            cout << "���������� � ����� �������: " << users.findUserByPassword(password) << endl;
            break;
        }
        case 2:
        {
            cout << "������ ��'� �����������: "; cin >> username;
            cout << "������ �����������: " << users.findPasswordByUsername(username) << endl;
            break;
        }
        case 3:
        {
            cout << "������ ������, ���� ������� �������: "; cin >> password;
            cout << "������ ����� ������: "; cin >> new_password;
            users.replacePassword(password, new_password);

            users.display();
            break;
        }
        case 4:
        {
            cout << "������ ��'� �����������: "; cin >> username;
            cout << "������ ������ �����������: "; cin >> password;
            cout << "������ ���� ��'�: "; cin >> new_username;
            users.replaceUsername(password, new_username);

            users.display();
            break;
        }
        case 5:
        {
            cout << "������ ���� ��'�: "; cin >> new_username;
            cout << "������ ������ ��� ����� �����������: "; cin >> new_password;
            users.add(new_password, new_username);

            users.display();
            break;
        }
        case 6:
        {
            cout << "������ ������ �����������, ����� ����� ��������: "; cin >> password;
            users.remove(password);

            users.display();
            break;
        }
        case 7:
        {
            cout << "������ ��'� �����������: "; cin >> username;
            cout << "������ ������: "; cin >> password;
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
            cout << "[ ERROR ]. ������� 䳿 ���� � ������. ��������� �� ���." << endl << endl;
        }
    } while (choice != 0);

    return 0;
}

