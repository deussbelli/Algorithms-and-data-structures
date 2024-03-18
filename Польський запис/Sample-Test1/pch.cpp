//
// pch.cpp
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;
bool isOperator(char token) {
    return (token == '+' || token == '-' || token == '*' || token == '/' || token == '%' ||
        token == '^' || token == '&' || token == '|' || token == '==' || token == '!=' ||
        token == '<' || token == '>' || token == '<=' || token == '>=');
}

bool isOperator(string token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" ||
        token == "^" || token == "&" || token == "|" || token == "==" || token == "!=" ||
        token == "<" || token == ">" || token == "<=" || token == ">=");
}

int getPrecedence(char op) {
    if (op == '>' || op == '<')
        return 7;
    if (op == '=>' || op == '>=')
        return 6;
    if (op == '|' || op == '&')
        return 5;
    if (op == '!' || op == '^')
        return 4;
    if (op == '*' || op == '/')
        return 3;
    if (op == '+' || op == '-')
        return 2;
    if (op == '&' || op == '|' || op == '%')
        return 1;
    if (op == '=' || op == '!=' || op == '==')
        return 0;
    return -1;
}

string infixToRPN(string expression) {
    stack<char> st;
    string result = "";
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == ' ')
            continue;
        if (expression[i] == '(') {
            st.push('(');
        }
        else if (expression[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty() && st.top() == '(')
                st.pop();
        }
        else if (isOperator(expression[i])) {
            while (!st.empty() && isOperator(st.top()) && getPrecedence(st.top()) >= getPrecedence(expression[i])) {
                result += st.top();
                st.pop();
            }
            st.push(expression[i]);
        }
        else {
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                result += expression[i];
                i++;
            }
            result += ' ';
            i--;
        }
    }
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
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
    else if (op == "%")
        return fmod(a, b);
    else {
        cout << "Некоректний арефметичний оператор чи значення змінної (можливе ділення на 0)." << endl;
        system("pause");
    }
}


double logicalOperation(double a, double b, string op) {
    if (op == "&break&")
        return a && b;
    else if (op == "|")
        return a || b;
    else if (op == "<")
        return a < b;
    else if (op == ">")
        return a > b;
    else if (op == "<=")
        return a <= b;
    else if (op == ">=")
        return a >= b;
    else if (op == "!=")
        return a != b;
    else if (op == "==")
        return a == b;
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
        if (isdigit(expression[i]) || expression[i] == '.') {
            size_t pos = expression.find(' ', i);
            if (pos == string::npos) {
                pos = expression.size();
            }
            token = expression.substr(i, pos - i);
            double value = stod(token);
            st.push(value);
            i = pos - 1;
        }
        else {
            b = st.top();
            st.pop();
            a = st.top();
            st.pop();
            st.push(arithmeticOperation(a, b, string(1, expression[i])));
        }
    }
    return st.top();
}

int test() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string expression;

    cout << "Уведіть вираз для конвертації у польский запис: ";
    getline(cin, expression);

    string rpnExpression = infixToRPN(expression);
    cout << "Зворотній польський запис: " << rpnExpression << endl;

    double result = evaluateRPN(rpnExpression);
    if (isnan(result)) {
        cout << "[ ERROR ] Наявне ділення на нуль." << endl;
    }
    else {
        cout << "Результат: " << result << endl;
    }

    return 0;
}



/*TEST(IsOperatorCharTest, ValidOperators) {
    EXPECT_TRUE(isOperator('+'));
    EXPECT_TRUE(isOperator('-'));
    EXPECT_TRUE(isOperator('*'));
    EXPECT_TRUE(isOperator('/'));
    EXPECT_TRUE(isOperator('%'));
    EXPECT_TRUE(isOperator('^'));
    EXPECT_TRUE(isOperator('&'));
    EXPECT_TRUE(isOperator('|'));
    EXPECT_TRUE(isOperator('<'));
    EXPECT_TRUE(isOperator('>'));
    EXPECT_TRUE(isOperator('<='));
    EXPECT_TRUE(isOperator('>='));

    EXPECT_FALSE(isOperator('('));
    EXPECT_FALSE(isOperator(')'));
    EXPECT_FALSE(isOperator(' '));
    EXPECT_FALSE(isOperator('1'));
    EXPECT_FALSE(isOperator('a'));
}*/

TEST(GetPrecedenceCharTest, InvalidPrecedences) {
    EXPECT_EQ(getPrecedence('('), -1);
    EXPECT_EQ(getPrecedence(')'), -1);
    EXPECT_EQ(getPrecedence(' '), -1);
    EXPECT_EQ(getPrecedence('a'), -1);
}

TEST(ArithmeticOperations, Add) {
    EXPECT_EQ(arithmeticOperation(2.5, 3.5, "+"), 6.0);
    EXPECT_EQ(arithmeticOperation(-2.5, 3.5, "+"), 1.0);
    EXPECT_EQ(arithmeticOperation(-2.5, -3.5, "+"), -6.0);
}

TEST(ArithmeticOperations, Subtract) {
    EXPECT_EQ(arithmeticOperation(2.5, 3.5, "-"), -1.0);
    EXPECT_EQ(arithmeticOperation(-2.5, 3.5, "-"), -6.0);
    EXPECT_EQ(arithmeticOperation(-2.5, -3.5, "-"), 1.0);
}

TEST(ArithmeticOperations, Multiply) {
    EXPECT_EQ(arithmeticOperation(2.5, 3.5, "*"), 8.75);
    EXPECT_EQ(arithmeticOperation(-2.5, 3.5, "*"), -8.75);
    EXPECT_EQ(arithmeticOperation(-2.5, -3.5, "*"), 8.75);
}

TEST(ArithmeticOperations, Divide) {
    EXPECT_EQ(arithmeticOperation(2.5, 5, "/"), 0.5);
    EXPECT_EQ(arithmeticOperation(-2.5, 5, "/"), -0.5);
    EXPECT_EQ(arithmeticOperation(-2.5, -5, "/"), 0.5);
}

TEST(ArithmeticOperations, Power) {
    EXPECT_EQ(arithmeticOperation(2, 2, "^"), 4);
    EXPECT_EQ(arithmeticOperation(2, 3, "^"), 8);
    EXPECT_EQ(arithmeticOperation(3, 2, "^"), 9);
}

TEST(ArithmeticOperations, Modulus) {
    EXPECT_EQ(arithmeticOperation(2.5, 3.5, "%"), 2.5);
    EXPECT_EQ(arithmeticOperation(-2.5, 3.5, "%"), -2.5);
    EXPECT_EQ(arithmeticOperation(-2.5, -3.5, "%"), -2.5);
}

TEST(LogicalOperations, And) {
    EXPECT_EQ(logicalOperation(true, true, "&break&"), true);
    EXPECT_EQ(logicalOperation(true, false, "&break&"), false);
    EXPECT_EQ(logicalOperation(false, true, "&break&"), false);
    EXPECT_EQ(logicalOperation(false, false, "&break&"), false);
}

TEST(LogicalOperations, Or) {
    EXPECT_EQ(logicalOperation(true, true, "|"), true);
    EXPECT_EQ(logicalOperation(true, false, "|"), true);
    EXPECT_EQ(logicalOperation(false, true, "|"), true);
    EXPECT_EQ(logicalOperation(false, false, "|"), false);
}



TEST(LogicalOperations, LessOperatorTrueOrFalse) {
    EXPECT_FALSE(logicalOperation(true, true, "<"));
    EXPECT_FALSE(logicalOperation(true, false, "<"));
    EXPECT_TRUE(logicalOperation(false, true, "<"));
    EXPECT_FALSE(logicalOperation(false, false, "<"));
}

TEST(LogicalOperations, GreaterOperatorTrueOrFalse) {
    EXPECT_FALSE(logicalOperation(true, true, ">"));
    EXPECT_TRUE(logicalOperation(true, false, ">"));
    EXPECT_FALSE(logicalOperation(false, true, ">"));
    EXPECT_FALSE(logicalOperation(false, false, ">"));
}

TEST(LogicalOperations, LessOrEqualOperatorTrueOrFalse) {
    EXPECT_TRUE(logicalOperation(true, true, "<="));
    EXPECT_FALSE(logicalOperation(true, false, "<="));
    EXPECT_TRUE(logicalOperation(false, true, "<="));
    EXPECT_TRUE(logicalOperation(false, false, "<="));
}

TEST(LogicalOperations, GreaterOrEqualOperatorTrueOrFalse) {
    EXPECT_TRUE(logicalOperation(true, true, ">="));
    EXPECT_TRUE(logicalOperation(true, false, ">="));
    EXPECT_TRUE(logicalOperation(false, false, ">="));
    EXPECT_FALSE(logicalOperation(false, true, ">="));
}


////////////examples
TEST(LogicalOperations, LessThan) {
EXPECT_EQ(logicalOperation(2.5, 3.5, "<"), true);
EXPECT_EQ(logicalOperation(-2.5, 3.5, "<"), true);
EXPECT_EQ(logicalOperation(-2.5, -1.5, "<"), true);
EXPECT_EQ(logicalOperation(-2.5, -0.5, "<"), true);
}

TEST(LogicalOperations, lessOrEqual) {
    EXPECT_EQ(logicalOperation(2.5, 3.5, "<="), true);
    EXPECT_EQ(logicalOperation(6.5, 3.5, "<="), false);
    EXPECT_EQ(logicalOperation(-2.5, -1.5, "<="), true);
    EXPECT_EQ(logicalOperation(-2.5, -2.5, "<="), true);
}

TEST(LogicalOperations, moreOrEqual) {
    EXPECT_EQ(logicalOperation(2.5, 3.5, ">="), false);
    EXPECT_EQ(logicalOperation(6.5, 3.5, ">="), true);
    EXPECT_EQ(logicalOperation(-2.5, -1.5, ">="), false);
    EXPECT_EQ(logicalOperation(-2.5, -2.5, ">="), true);
}

TEST(LogicalOperations, Equal) {
    EXPECT_EQ(logicalOperation(2.5, 2.5, "=="), true);
    EXPECT_EQ(logicalOperation(6.5, 3.5, "=="), false);
    EXPECT_EQ(logicalOperation(-2.5, -1.5, "=="), false);
    EXPECT_EQ(logicalOperation(-2.5, -2.5, "=="), true);
}

TEST(LogicalOperations, notEqual) {
    EXPECT_EQ(logicalOperation(2.5, 3.5, "!="), true);
    EXPECT_EQ(logicalOperation(6.5, 3.5, "!="), true);
    EXPECT_EQ(logicalOperation(-2.5, -1.5, "!="), true);
    EXPECT_EQ(logicalOperation(-2.5, -2.5, "!="), false);
}


TEST(ExpressionTests, Example1) {
    EXPECT_EQ((3+7)/2, 5);
}

TEST(ExpressionTests, Example2) {
    EXPECT_EQ((5 * (2 + 4)) / 6 - 1, 4);
}

TEST(ExpressionTests, Example3) {
    EXPECT_EQ((1 + (2 * 3) + 4 - (6 / 6)), 10);
}

TEST(ExpressionTests, Example4) {
    EXPECT_EQ(((1+9)/(11+12)+(5/(23-3))), 0); /*0.68478260869*/
}

TEST(ExpressionTests, Example5) {
    EXPECT_EQ(pow(2, pow(3, 2)), 512);
}

TEST(ExpressionTests, Example6) {
    EXPECT_EQ(7 % 3, 1);
}

TEST(ExpressionTests, Example7) {
    EXPECT_EQ(!(3 > 2), false);
}

TEST(ExpressionTests, Example8) {
    EXPECT_EQ(2 | 3, 3);
}

TEST(ExpressionTests, Example9) {
    EXPECT_EQ(1 < 2 && 3 > 4, false);
}

TEST(ExpressionTests, Example10) {
    EXPECT_EQ(1 < 2 || 3 > 4 && 5 <= 6, true);
}