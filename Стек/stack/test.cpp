#include "pch.h"

#include <gtest/gtest.h>
#include <stack>
#include <windows.h>

using namespace std;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    stack<int> myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    cout << "Розмірність стеку: " << myStack.size() << endl;

    if (myStack.empty()) {
        cout << "Стек пустий." << endl;
    }
    else {
        cout << "Стек містить елементи." << endl;
    }

    int value;

    cout << endl << "Перевірка останнього елементу. \nУведіть число: ";
    cin >> value;

    if (myStack.top() == value) {
        cout << "Число " << value << " є останнім внесеним у стек." << endl << endl;
    }
    else {
        cout << "Число " << value << " не є останнім внесеним у стек." << endl << endl;
    }

    cout << "Останній елемент у стеці: " << myStack.top() << endl;
    myStack.pop();
    cout << "Перший внесений елемент у стек: " << myStack.top() - 1 << endl << endl;


    cout << "Адреса останньго (вернхнього) елемента: " << &(myStack.top()) << endl;
    cout << "Адреса першого (нижнього) елемента: " << &(myStack.top()) - (2 * 4) << endl;

    return 0;
}

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        myStack.push(1);
        myStack.push(2);
        myStack.push(3);
    }

    void TearDown() override {
        while (!myStack.empty()) {
            myStack.pop();
        }
    }

    stack<int> myStack;
};


//розмірність
TEST_F(StackTest, SizeTest) {
    ASSERT_EQ(myStack.size(), 3);
}

//чи пустий
TEST_F(StackTest, EmptyTest) {
    ASSERT_FALSE(myStack.empty());
    myStack.pop();
    myStack.pop();
    myStack.pop();
    ASSERT_TRUE(myStack.empty());
}

//Top
TEST_F(StackTest, TopTest) {
    ASSERT_EQ(myStack.top(), 3);
    myStack.pop();
    ASSERT_EQ(myStack.top(), 2);
}

//Pop
TEST_F(StackTest, PopTest) {
    myStack.pop();
    ASSERT_EQ(myStack.top(), 2);
}

//Push
TEST_F(StackTest, PushTest) {
    myStack.push(4);
    ASSERT_EQ(myStack.top(), 4);
}

//Push + pop
TEST_F(StackTest, MultiplePushPopTest) {
    myStack.push(4);
    myStack.push(5);
    myStack.pop();
    ASSERT_EQ(myStack.top(), 4);
}

//додаємо і перевіряємо розмірність
TEST_F(StackTest, PushIncreasesSize) {
    myStack.push(5);
    ASSERT_EQ(myStack.size(), 4);
    myStack.push(6);
    ASSERT_EQ(myStack.size(), 5);
}

//видаляємо та перевіряємо розмірність
TEST_F(StackTest, PopDecreasesSize) {
    myStack.push(4);
    myStack.push(5);
    myStack.pop();
    ASSERT_EQ(myStack.size(), 4);
    myStack.pop();
    ASSERT_EQ(myStack.size(), 3);
}

//додаємо і перевіряємо розмірність 
TEST_F(StackTest, PeekReturnsTop) {
    myStack.push(4);
    myStack.push(5);
    ASSERT_EQ(myStack.top(), 5);
}





