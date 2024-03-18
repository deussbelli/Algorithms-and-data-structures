//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <string>
#include <math.h>
#include <stack>

using namespace std;

bool isOperator(string token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "&&" || token == "||" || token == "!" || token == "^");
}

double arithmeticOperation(double a, double b, string op) {
    if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "*")
        return a * b;
    else if (op == "/" && b != 0)
        return a / b;
    else if (op == "^")
        return pow(a, b);
    else {
        cout << "Некоректний арефметичний оператор чи значення змінної." << endl;
        system("pause"); 
    }
}

double logicalOperation(double a, double b, string op) {
    if (op == "&break&")
        return a && b;
    else if (op == "||")
        return a || b;
    else if (op == "!")
        return !a;
    else {
        cout << "Некоректний логічний оператор чи значення змінної." << endl;
        system("pause");
    }
}

double evaluateRPN(string expression) {
    stack<double> st;
    string token;
    double a, b;
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == ' ')
            continue;
        if (expression[i] == '(') {
            // находим позицию закрывающей скобки
            int j = i + 1;
            int open = 1;
            while (j < expression.size() && open > 0) {
                if (expression[j] == '(')
                    open++;
                else if (expression[j] == ')')
                    open--;
                j++;
            }
            // вычисляем значение выражения в скобках
            double value = evaluateRPN(expression.substr(i + 1, j - i - 2));
            st.push(value);
            i = j - 1;
        }
        else if (isOperator(token = expression.substr(i, expression.find(' ', i) - i))) {
            b = st.top();
            st.pop();
            a = st.top();
            st.pop();
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
                st.push(arithmeticOperation(a, b, token));
            }
            else {
                st.push(logicalOperation(a, b, token));
            }
            i = expression.find(' ', i);
        }
        else {
            st.push(stod(token));
            i = expression.find(' ', i);
        }
    }
    return st.top();
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string expression;

    cout << "Уведіть вираз для обчислення: ";
    getline(cin, expression);

    double result = evaluateRPN(expression);
    cout << "Результат: " << result << endl;

    return 0;
}

TEST(IsOperatorTest, ValidOperators) {
    ASSERT_TRUE(isOperator("+"));
    ASSERT_TRUE(isOperator("-"));
    ASSERT_TRUE(isOperator("*"));
    ASSERT_TRUE(isOperator("/"));
    ASSERT_TRUE(isOperator("^"));
    ASSERT_TRUE(isOperator("&&"));
    ASSERT_TRUE(isOperator("||"));
    ASSERT_TRUE(isOperator("!"));
}

TEST(isOperatorTest, InvalidOperatorToken) {
    EXPECT_FALSE(isOperator("1"));
    EXPECT_FALSE(isOperator("true"));
    EXPECT_FALSE(isOperator("&"));
}


TEST(IsOperatorTest, InvalidOperators) {
    ASSERT_FALSE(isOperator(""));
    ASSERT_FALSE(isOperator("abc"));
    ASSERT_FALSE(isOperator("&"));
    ASSERT_FALSE(isOperator("|||"));
}

TEST(ArithmeticOperationTest, Addition) {
    ASSERT_EQ(arithmeticOperation(2, 3, "+"), 5);
    ASSERT_EQ(arithmeticOperation(-2, 3, "+"), 1);
    ASSERT_EQ(arithmeticOperation(0, 0, "+"), 0);
}

TEST(ArithmeticOperationTest, Subtraction) {
    ASSERT_EQ(arithmeticOperation(2, 3, "-"), -1);
    ASSERT_EQ(arithmeticOperation(-2, 3, "-"), -5);
    ASSERT_EQ(arithmeticOperation(0, 0, "-"), 0);
}

TEST(ArithmeticOperationTest, Multiplication) {
    ASSERT_EQ(arithmeticOperation(2, 3, "*"), 6);
    ASSERT_EQ(arithmeticOperation(-2, 3, "*"), -6);
    ASSERT_EQ(arithmeticOperation(0, 0, "*"), 0);
}


TEST(ArithmeticOperationTest, Division) {
    ASSERT_EQ(arithmeticOperation(3, 2, "/"), 1.5);
    ASSERT_EQ(arithmeticOperation(3, -2, "/"), -1.5);
    ASSERT_THROW(arithmeticOperation(2, 0, "/"), invalid_argument);
}

TEST(ArithmeticOperationTest, Exponentiation) {
    ASSERT_EQ(arithmeticOperation(2, 3, "^"), 8);
    ASSERT_EQ(arithmeticOperation(-2, 3, "^"), -8);
    ASSERT_EQ(arithmeticOperation(0, 0, "^"), 1);
}

TEST(LogicalOperationTest, LogicalAnd) {
    ASSERT_EQ(logicalOperation(1, 1, "&&"), true);
    ASSERT_EQ(logicalOperation(1, 0, "&&"), false);
    ASSERT_EQ(logicalOperation(0, 1, "&&"), false);
    ASSERT_EQ(logicalOperation(0, 0, "&&"), false);

    EXPECT_EQ(logicalOperation(true, false, "&&"), false);
    EXPECT_EQ(logicalOperation(true, true, "&&"), true);
}

TEST(LogicalOperationTest, LogicalOr) {
    ASSERT_EQ(logicalOperation(1, 1, "||"), true);
    ASSERT_EQ(logicalOperation(1, 0, "||"), true);
    ASSERT_EQ(logicalOperation(0, 1, "||"), true);
    ASSERT_EQ(logicalOperation(0, 0, "||"), false);

    EXPECT_EQ(logicalOperation(true, false, "||"), true);
    EXPECT_EQ(logicalOperation(false, false, "||"), false);
}

TEST(logicalOperationTest, LogicalNOT) {
    EXPECT_EQ(logicalOperation(true, false, "!"), false);
    EXPECT_EQ(logicalOperation(false, false, "!"), true);
}
