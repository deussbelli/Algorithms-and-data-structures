//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

class MyString {
private:
    string data;

public:
    MyString() {
        data = "";
    }

    MyString(string str) {
        data = str;
    }

    string getData() const {
        return data;
    }

    void setData(string str) {
        data = str;
    }

    MyString operator+(const MyString& other) const {
        MyString result(data + other.getData());
        return result;
    }
};

MyString unaryToBinary(const MyString& unaryStr) {
    int numOnes = 0;
    for (char c : unaryStr.getData()) {
        if (c == '1' || c == '|') {
            numOnes++;
        }
        else if (c == '0') {
            continue;
        }
        else {
            throw runtime_error("Помилка: неправильний формат даних.");
        }
    }
    string binaryStr = "";
    while (numOnes > 0) {
        binaryStr = to_string(numOnes % 2) + binaryStr;
        numOnes /= 2;
    }
    return MyString(binaryStr);
}


MyString binaryToUnary(MyString binaryNum) {
    string binaryStr = binaryNum.getData();
    int num = 0;
    for (int i = 0; i < binaryStr.length(); i++) {
        num *= 2;
        num += (binaryStr[i] - '0');
    }
    string unaryNum = "";
    for (int i = 0; i < num; i++) {
        unaryNum += "1";
    }
    return MyString(unaryNum);
}

MyString multiply(const MyString& stickStr1, const MyString& stickStr2) {
    int num1 = stickStr1.getData().size();
    int num2 = stickStr2.getData().size();
    string resultStr = "";
    for (int i = 0; i < num1; i++) {
        for (int j = 0; j < num2; j++) {
            resultStr += "|";
        }
    }
    return MyString(resultStr);
}

MyString divide(const MyString& stickStr1, const MyString& stickStr2) {
    int num1 = stickStr1.getData().size();
    int num2 = stickStr2.getData().size();
    if (num1 % num2 != 0 || num2 == 0 || num1 == 0) {
        throw runtime_error("Помилка: неправильний формат даних.");
    }
    int result = num1 / num2;
    string resultStr = "";
    for (int i = 0; i < result; i++) {
        resultStr += "|";
    }
    return MyString(resultStr);
}

MyString subtract(const MyString& stickStr1, const MyString& stickStr2) {
    int num1 = stickStr1.getData().size();
    int num2 = stickStr2.getData().size();
    if (num1 <= num2) {
        throw runtime_error("Помилка: неправильний формат даних.");
    }
    string resultStr = "";
    for (int i = 0; i < num1 - num2; i++) {
        resultStr += "|";
    }
    return MyString(resultStr);
}

MyString add(const MyString& stickStr1, const MyString& stickStr2) {
    int num1 = stickStr1.getData().size();
    int num2 = stickStr2.getData().size();
    int result = num1 + num2;
    string resultStr = "";
    for (int i = 0; i < result; i++) {
        resultStr += "|";
    }
    return MyString(resultStr);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string input;
    MyString unaryStr, stickStr1, stickStr2;

    cout << "Уведіть унарне число [|]: ";
    getline(cin, input);
    unaryStr.setData(input);

    cout << "Уведіть бінарне число [|]: ";
    getline(cin, input);
    MyString binaryNum(input);
    cout << endl;

    cout << "Уведіть перший рядок символів [|]: ";
    getline(cin, input);
    stickStr1.setData(input);

    cout << "Уведіть другий рядок символів [|]: ";
    getline(cin, input);
    stickStr2.setData(input);

    while (true) {
        cout << "\n [ Обрати дію ]:\n";
        cout << "1. Конвертувати унарне число у бінарне, показати звичайне.\n";
        cout << "2. Помножити перший рядок на другий.\n";
        cout << "3. Розділити перший рядок на другий.\n";
        cout << "4. Відняти від першого рядка другий.\n";
        cout << "5. Додати два рядки.\n";
        cout << "6. Конвертувати бінарне число в унарне, показати унарне звичайне.\n";
        cout << "7. Вийти.\n";
        cout << " [ Обрати ]: ";

        int choice;
        cin >> choice;
        cin.ignore(); 
        cout << "_______________________________________\n\n";

        if (choice == 1) {
            auto start = chrono::steady_clock::now();
            MyString binaryStr = unaryToBinary(unaryStr);
            auto end = chrono::steady_clock::now();
            cout << "Результат конвертації: " << binaryStr.getData() << endl;
            cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
            cout << "_______________________________________\n";
        }
        else if (choice == 2) {
                auto start = chrono::steady_clock::now();
                MyString result = multiply(stickStr1, stickStr2);
                auto end = chrono::steady_clock::now();
                cout << "Результат множення: " << result.getData() << endl;
                cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
                cout << "_______________________________________\n";
        }
        else if (choice == 3) {
            if (stickStr2.getData().size() > 0 && stickStr1.getData().size() % stickStr2.getData().size() == 0) {
                auto start = chrono::steady_clock::now();
                MyString result = divide(stickStr1, stickStr2);
                auto end = chrono::steady_clock::now();
                cout << "Результат ділення: " << result.getData() << endl;
                cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
                cout << "_______________________________________\n";
            }
            else {
                cout << "Помилка: другий рядок має бути не більшим за перший та ділитися без остачі.\n";
                cout << "_______________________________________\n";
            }
        }
        else if (choice == 4) {
            if (stickStr1.getData().size() >= stickStr2.getData().size()) {
                auto start = chrono::steady_clock::now();
                MyString result = subtract(stickStr1, stickStr2);
                auto end = chrono::steady_clock::now();
                cout << "Результат віднімання: " << result.getData() << endl;
                cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
                cout << "_______________________________________\n";
            }
            else {
                cout << "Помилка: другий рядок має бути не більшим за перший.\n";
                cout << "_______________________________________\n";
            }
        }
        else if (choice == 5) {
            auto start = chrono::steady_clock::now();
            MyString sum = add(stickStr1, stickStr2);
            auto end = chrono::steady_clock::now();
            cout << "Результат додавання: " << sum.getData() << endl;
            cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
            cout << "_______________________________________\n";
        }
        else if (choice == 6) {
            auto start = chrono::steady_clock::now();
            MyString convertedUnary = binaryToUnary(binaryNum);
            auto end = chrono::steady_clock::now();
            cout << "Результат конвертації: " << convertedUnary.getData() << endl;
            cout << "Час виконання: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " мікросекунд." << endl;
            cout << "_______________________________________\n";
        }
        else if (choice == 7) {
            cout << "Вихід." << endl;
            cout << "_______________________________________\n";
            break;
        }
        else {
            cout << "Неккоректно обрано дію. Спробуйте знову." << endl;
            cout << "_______________________________________\n";
        }
    }
    return 0;
}

class MyStringTest : public ::testing::Test {
protected:
    MyString s1, s2;

    void SetUp() override {
        s1.setData("");
        s2.setData("");
    }
};


TEST_F(MyStringTest, UnaryToBinaryTest) {
    MyString unaryStr("|||");
    MyString binaryStr = unaryToBinary(unaryStr);
    EXPECT_EQ(binaryStr.getData(), "11");
}

// Test case for multiply function
TEST_F(MyStringTest, MultiplyTest) {
    MyString stickStr1("||||");
    MyString stickStr2("||");
    MyString result = multiply(stickStr1, stickStr2);
    EXPECT_EQ(result.getData(), "||||||||");
}

// Test case for divide function
TEST_F(MyStringTest, DivideTest) {
    MyString stickStr1("||||||");
    MyString stickStr2("|||");
    MyString result = divide(stickStr1, stickStr2);
    EXPECT_EQ(result.getData(), "||");
}

// Test case for subtract function
TEST_F(MyStringTest, SubtractTest) {
    MyString stickStr1("||||||");
    MyString stickStr2("||");
    MyString result = subtract(stickStr1, stickStr2);
    EXPECT_EQ(result.getData(), "||||");
}

// Test case for add function
TEST_F(MyStringTest, AddTest) {
    MyString stickStr1("||||");
    MyString stickStr2("|||");
    MyString result = add(stickStr1, stickStr2);
    EXPECT_EQ(result.getData(), "|||||||");
}

// Test case for exception in divide function
TEST_F(MyStringTest, DivideExceptionTest) {
    MyString stickStr1("|||||");
    MyString stickStr2("|||");
    EXPECT_THROW(divide(stickStr1, stickStr2), runtime_error);
}


TEST_F(MyStringTest, UnaryToBinary) {
    MyString unaryStr("111|11");
    MyString binaryStr = unaryToBinary(unaryStr);
    EXPECT_EQ("110", binaryStr.getData());
}

TEST_F(MyStringTest, BinaryToUnary) {
    MyString binaryStr("1011");
    MyString unaryStr = binaryToUnary(binaryStr);
    EXPECT_EQ("11111111111", unaryStr.getData());
}