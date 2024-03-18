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

    cout << "��������� �����: " << myStack.size() << endl;

    if (myStack.empty()) {
        cout << "���� ������." << endl;
    }
    else {
        cout << "���� ������ ��������." << endl;
    }

    int value;

    cout << endl << "�������� ���������� ��������. \n������ �����: ";
    cin >> value;

    if (myStack.top() == value) {
        cout << "����� " << value << " � ������� �������� � ����." << endl << endl;
    }
    else {
        cout << "����� " << value << " �� � ������� �������� � ����." << endl << endl;
    }

    cout << "������� ������� � �����: " << myStack.top() << endl;
    myStack.pop();
    cout << "������ �������� ������� � ����: " << myStack.top() - 1 << endl << endl;


    cout << "������ ��������� (����������) ��������: " << &(myStack.top()) << endl;
    cout << "������ ������� (��������) ��������: " << &(myStack.top()) - (2 * 4) << endl;

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


//���������
TEST_F(StackTest, SizeTest) {
    ASSERT_EQ(myStack.size(), 3);
}

//�� ������
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

//������ � ���������� ���������
TEST_F(StackTest, PushIncreasesSize) {
    myStack.push(5);
    ASSERT_EQ(myStack.size(), 4);
    myStack.push(6);
    ASSERT_EQ(myStack.size(), 5);
}

//��������� �� ���������� ���������
TEST_F(StackTest, PopDecreasesSize) {
    myStack.push(4);
    myStack.push(5);
    myStack.pop();
    ASSERT_EQ(myStack.size(), 4);
    myStack.pop();
    ASSERT_EQ(myStack.size(), 3);
}

//������ � ���������� ��������� 
TEST_F(StackTest, PeekReturnsTop) {
    myStack.push(4);
    myStack.push(5);
    ASSERT_EQ(myStack.top(), 5);
}





