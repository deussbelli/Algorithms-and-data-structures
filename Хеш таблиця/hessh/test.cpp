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

TEST(HashTableTest, AddElement) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    EXPECT_EQ("JohnDoe", ht.findUserByPassword("password123"));
}

TEST(HashTableTest, FindUserByPassword) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    EXPECT_EQ("JohnDoe", ht.findUserByPassword("password123"));
    EXPECT_EQ("Коритувача з таким паролем не знайдено.", ht.findUserByPassword("wrongpassword"));
}

TEST(HashTableTest, FindPasswordByUsername) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    EXPECT_EQ("password123", ht.findPasswordByUsername("JohnDoe"));
    EXPECT_EQ("Уведенего паролю не знайдено у базі даних.", ht.findPasswordByUsername("JaneDoe"));
}

TEST(HashTableTest, ReplacePassword) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    ht.replacePassword("password123", "newpassword");
    EXPECT_EQ("JohnDoe", ht.findUserByPassword("newpassword"));
    EXPECT_EQ("Коритувача з таким паролем не знайдено.", ht.findUserByPassword("password123"));
}

TEST(HashTableTest, ReplaceUsername) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    ht.replaceUsername("password123", "JaneDoe");
    EXPECT_EQ("password123", ht.findPasswordByUsername("JaneDoe"));
    EXPECT_EQ("Уведенего паролю не знайдено у базі даних.", ht.findPasswordByUsername("JohnDoe"));
}

TEST(HashTableTest, RemoveByPassword) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    ht.remove("password123");
    EXPECT_EQ("Коритувача з таким паролем не знайдено.", ht.findUserByPassword("password123"));
}

TEST(HashTableTest, RemoveByPasswordAndUsername) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    ht.remove("password123", "JohnDoe");
    EXPECT_EQ("Коритувача з таким паролем не знайдено.", ht.findUserByPassword("password123"));
}

TEST(HashTableTest, DisplayTable) {
    HashTable ht;
    ht.add("password123", "JohnDoe");
    ht.add("password456", "JaneDoe");
    testing::internal::CaptureStdout();
    ht.display();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("[ Пароль ]\t[ Ім'я користувача ]\npassword123\t\tJohnDoe\npassword456\t\tJaneDoe\n", output);
}