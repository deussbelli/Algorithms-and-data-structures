#include "pch.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <windows.h>
#include <string>
#include <math.h>
#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

// Function to check if a given token is an operator
bool isOperator(string token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "&&" || token == "||" || token == "!" || token == "^");
}

// Function to perform arithmetic operations
double arithmeticOperation(double a, double b, string op) {
    if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "*")
        return a * b;
    else if (op == "/")
        return a / b;
    else if (op == "^")
        return pow(a, b);
    else {
        cout << "Некоректний арефметичний оператор." << endl;
        return 0;
    }
}

// Function to perform logical operations
double logicalOperation(double a, double b, string op) {
    if (op == "&&")
        return a && b;
    else if (op == "||")
        return a || b;
    else if (op == "!")
        return !a;
    else {
        cout << "Некоректний логічний оператор." << endl;
        return 0;
    }
}

// Function to evaluate the expression in reverse Polish notation
double evaluateRPN(string expression) {
    stack<double> st;
    string token;
    double a, b;
    for (int i = 0; i < expression.size(); i++) {
        // If current character is a delimiter, skip it
        if (expression[i] == ' ')
            continue;
        // If current token is an operator, pop two operands and perform the operation
        if (isOperator(token = expression.substr(i, expression.find(' ', i) - i))) {
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
        // If current token is an operand, push it onto the stack
        else {
            st.push(stod(token));
            i = expression.find(' ', i);
        }
    }
    // The final result will be at the top of the stack
    return st.top();
}

int test() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string expression;

    cout << "Уведіть вираз для обчислення: ";
    getline(cin, expression);

    double result = evaluateRPN(expression);
    cout << "Результат: " << result << endl;

    return 0;
}


// Test case for evaluating arithmetic expression "2 3 + 4 *"
TEST(RPNCalculatorTest, ArithmeticExpression1) {
    EXPECT_EQ(evaluateRPN("2 3 + 4 *"), 20);
}

// Test case for evaluating arithmetic expression "3 4 * 2 /"
TEST(RPNCalculatorTest, ArithmeticExpression2) {
    EXPECT_EQ(evaluateRPN("3 4 * 2 /"), 6);
}

// Test case for evaluating arithmetic expression "5 2 3 * +"
TEST(RPNCalculatorTest, ArithmeticExpression3) {
    EXPECT_EQ(evaluateRPN("5 2 3 * +"), 11);
}

// Test case for evaluating logical expression "1 0 && ! 0 ||"
TEST(RPNCalculatorTest, LogicalExpression1) {
    EXPECT_EQ(evaluateRPN("1 0 && ! 0 ||"), 1);
}

// Test case for evaluating logical expression "1 1 && 0 ||"
TEST(RPNCalculatorTest, LogicalExpression2) {
    EXPECT_EQ(evaluateRPN("1 1 && 0 ||"), 0);
}

// Test case for evaluating expression "2 3 + 4 * !"
TEST(RPNCalculatorTest, InvalidExpression1) {
    EXPECT_EQ(evaluateRPN("2 3 + 4 * !"), 0);
}

// Test case for evaluating expression "2 + 3 * 4"
TEST(RPNCalculatorTest, InvalidExpression2) {
    EXPECT_EQ(evaluateRPN("2 + 3 * 4"), 0);
}

// Test case for evaluating expression "1 2 3"
TEST(RPNCalculatorTest, InvalidExpression3) {
    EXPECT_EQ(evaluateRPN("1 2 3"), 0);
}

// Test case for evaluating expression "3 / 0"
TEST(RPNCalculatorTest, DivideByZero) {
    EXPECT_EQ(evaluateRPN("3 0 /"), INFINITY);
}

// Test case for evaluating expression "2 ^ 3"
TEST(RPNCalculatorTest, ExponentialExpression) {
    EXPECT_EQ(evaluateRPN("2 3 ^"), 8);
}
