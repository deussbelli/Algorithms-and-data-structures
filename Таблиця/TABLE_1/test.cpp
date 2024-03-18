#include "pch.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <fcntl.h>
#include <map>

using namespace std;

struct Product {
    string name;
    double price;
};

void info()
{
    system("cls");

    cout << "[ DONE ]     Інформацію оновлено.\n\n";

    cout << "КОД " << "    НАЗВА    " << "               ЦІНА ";

    _setmode(_fileno(stdout), _O_WTEXT);
    wcout << "[" << (wchar_t)0x20B4 << "]" << "\n";
    _setmode(_fileno(stdout), _O_TEXT);

    cout << "______________________________________________________" << endl;
}

int test() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Таблиця продуктів:\n\n";

    cout << "КОД " << "    НАЗВА    " << "               ЦІНА ";

    _setmode(_fileno(stdout), _O_WTEXT);
    wcout << "[" << (wchar_t)0x20B4 << "]" << "\n";
    _setmode(_fileno(stdout), _O_TEXT);

    cout << "______________________________________________________" << endl;

    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129}},
        {"1005", {"Ананас  ", 140}},
        {"1006", {"Ківі    ", 123.90}},
        {"1007", {"Манго    ", 199}},
        {"1008", {"Маракуйя ", 239}},
        {"1009", {"Капуста ", 19.80}},
        {"1010", {"Картопля ", 39.99}},
        {"1011", {"Цибуля   ", 23.99}},
        {"1012", {"Часник  ", 89.99}},
        {"1013", {"Гарбуз   ", 26.49}},
        {"1014", {"Диня     ", 16.99}},
        {"1015", {"Кавун    ", 15.99}},
        {"1016", {"Вода    ", 17}},
        {"1017", {"Вино     ", 199.99}},
        {"10171", {"Сік апельсин", 49.78} },
        {"1018", {"Сік груша   ", 54.99}},
        {"1019", {"Сік мандарин   ", 65.99}},
        {"1020", {"Сік слива   ", 52.99}},
        {"1021", {"Сік вишня    ", 51.99}},
        {"1022", {"Огірок     ", 29.49}},
        {"1023", {"Помідор     ", 42.99}},
        {"1024", {"Сир       ", 149.99}},
        {"1025", {"Молоко     ", 38.49}},
        {"1026", {"Йогурт   ", 62.99}},
        {"1028", {"Макарони  ", 89.99}},
        {"1029", {"Вермішель  ", 73.49}},
        {"1030", {"Паста    ", 84.99}},
        {"1035", {"Хліб      ", 15.99}},
        {"1031", {"Борошно   ", 42.99}},
        {"1032", {"Сіль    ", 21.99}},
        {"1033", {"Цукор    ", 37.49}},
        {"1034", {"Куркума   ", 150.99}},
        {"1036", {"Перець    ", 250.99}},
        {"1037", {"Олія рослинна", 82.99}},
        {"1038", {"Олія соняшник", 51.99}},
        {"1039", {"Олія маслинна", 339.49}},
        {"1040", {"Риба     ", 200.99}},
        {"1041", {"М'ясо   ", 258.99}},
        {"1042", {"Консерви", 240.99}},
        {"1043", {"Печінка   ", 199.99}},
        {"1044", {"Крильця  ", 340.49}},
        {"1045", {"Гомілка  ", 450.99}},
        {"1046", {"Вирізка   ", 580.99}},
        {"1047", {"Шашлик   ", 2002.99}},
        {"1048", {"Серветки ", 17.99}},
        {"1049", {"Столові прибори", 340.49}},
        {"1050", {"Рушник  ", 404.99}},
    };

    for (const auto& [code, product] : productTable) {
        cout << code << "\t" << product.name << "\t\t" << product.price << "\t" << " [за кг/л/шт.]\n";
    }
    cout << endl << endl;

    string code;
    cout << "  [ Пошук продукту ]\nУведіть код продукту: ";
    cin >> code; cout << endl;

    if (productTable.find(code) == productTable.end()) {
        cout << "\n[ ERROR ]     Продукту не знайдено.\n";
    }
    else {
        Product& product = productTable[code];
        cout << "Найменування: " << product.name << endl;
        cout << "Ціна за кілограм: " << product.price << endl << endl;
    }

    cout << "                                  Чи бажаєте ви редагувати інформацію? \n                                                [ + | - ]" << endl;
    char click;
    cout << "                                                    "; cin >> click;

    if (click == '+')
    {
        cout << " 1] Оновити інформацію продукту, що міститься у таблиці;\n"
            << " 2] Додати новий рядок до таблиці; \n"
            << " 3] Вилучити рядок з таблиці. \n\n"
            << "    Оберіть дію: ";
    }
    else
    {
        return 0;
    }

    char response;
    cin >> response;

    string name;
    double price;
    string codecheck;
    string codepush;

    if (response == '1')
    {
        cout << "\n Уведіть код продукту: ";
        cin >> codepush;
        if (productTable.find(codepush) == productTable.end())
        {
            cout << "\n[ ERROR ]     Продукту не знайдено.\n";
            return 0;
        }
        else
        {
            cout << "\nПродукт міститься у базі, переходимо до оновлення інформації.\n\n";
        }

        cout << "Уведіть найменування: ";
        cin >> name;
        cout << "Уведіть нову ціну: ";
        cin >> price;

        Product& product = productTable[codepush];
        code = codepush;
        product.name = name;
        product.price = price;

        info();

        for (const auto& [code, product] : productTable) {
            cout << code << "\t" << product.name << "\t\t" << product.price << "\t" << " [за кг/л/шт.]\n";
        }
        cout << endl;
    }

    if (response == '2')
    {
        cout << "\nУведіть код продукту: "; cin >> codepush;
        cout << "Уведіть назву продукту: "; cin >> name;
        cout << "Уведіть вартість: "; cin >> price;

        Product& product = productTable[codepush];
        code = codepush;
        product.name = name;
        product.price = price;

        productTable.insert({ codecheck, {name, price} });

        info();

        for (const auto& [code, product] : productTable) {
            cout << code << "\t" << product.name << "\t\t" << product.price << "\t" << " [за кг/л/шт.]\n";
        }
        cout << endl << endl;
    }

    if (response == '3')
    {
        cout << "\nУведіть код продукту, котрий потрібно вилучити "; cin >> codecheck;

        Product& product = productTable[codecheck];
        code = codecheck;

        productTable.erase(codecheck);

        info();

        for (const auto& [code, product] : productTable) {
            cout << code << "\t" << product.name << "\t\t" << product.price << "\t" << " [за кг/л/шт.]\n";
        }
        cout << endl << endl;
    }

    return 0;
}



//////////////////////////////////////////////////////////
//////////////////////тестування//////////////////////////
//////////////////////////////////////////////////////////


#include "gtest/gtest.h"

//чи пуста таблиця
TEST(ProductTableTest, CheckIfProductTableIsEmpty) {
    map<string, Product> productTable;
    ASSERT_EQ(productTable.size(), 0);
}

//чи міститься продукт
TEST(ProductTableTest, ProductExists) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
    };
    string code = "1002";
    auto it = productTable.find(code);

    EXPECT_NE(it, productTable.end());
}

//продукт не знайдено
TEST(ProductTableTest, ProductNotFound) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
    };
    string code = "1004";

    auto it = productTable.find(code);

    EXPECT_EQ(it, productTable.end());
}

//показ корректного виводу
TEST(ProductTableTest, CorrectProductInfoDisplayed) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
    };
    string code = "1002";
    testing::internal::CaptureStdout(); 

    const auto& product = productTable[code];
    cout << code << "\t" << product.name << "\t\t" << product.price << "\t" << " [за кг/л/шт.]\n";
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1002\tГруша   \t\t17.9\t [за кг/л/шт.]\n");
}

//показ "неккоректності" інформації
TEST(ProductTableTest, IncorrectProductCodeEntered) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
    };
    string code = "1004";
    testing::internal::CaptureStdout(); 

    if (productTable.find(code) == productTable.end()) {
        cout << "\n[ ERROR ]     Продукту не знайдено...";
    }
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n[ ERROR ]     Продукту не знайдено...");
}

//корректна інформація
TEST(ProductTableTest, CheckIfProductInformationIsCorrect) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129}}
    };
    string code = "1003";
    ASSERT_EQ(productTable[code].name, "Апельсин");
    ASSERT_EQ(productTable[code].price, 37);
}

//к-ть продуктів у таблиці
TEST(ProductTableTest, CheckIfProductTableHasProducts) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129}}
    };
    ASSERT_EQ(productTable.size(), 4);
}

//чи міститься продукт
TEST(ProductTableTest, CheckIfProductExistsInTable) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129}}
    };
    string code = "1003";
    ASSERT_NE(productTable.find(code), productTable.end());
}

//якщо не міститься
TEST(ProductTableTest, CheckIfProductDoesNotExistInTable) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко  ", 12.50}},
        {"1002", {"Груша   ", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129}}
    };
    string code = "1005";
    ASSERT_EQ(productTable.find(code), productTable.end());
}

//додаємо продукт
TEST(ProductTableTest, AddNewProduct) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко", 12.50}},
        {"1002", {"Груша", 17.90}},
        {"1003", {"Апельсин", 37}}
    };

    string codecheck = "1004";
    string name = "Виноград";
    double price = 129.0;

    productTable.insert({ codecheck, {name, price} });

    EXPECT_EQ(productTable.size(), 4);
    EXPECT_EQ(productTable[codecheck].name, name);
    EXPECT_EQ(productTable[codecheck].price, price);
}

//прибираємо продукт
TEST(ProductTableTest, RemoveProduct) {
    map<string, Product> productTable = {
        {"1001", {"Яблуко", 12.50}},
        {"1002", {"Груша", 17.90}},
        {"1003", {"Апельсин", 37}},
        {"1004", {"Виноград", 129.0}}
    };

    string codecheck = "1004";

    productTable.erase(codecheck);

    EXPECT_EQ(productTable.size(), 3);
    EXPECT_EQ(productTable.find(codecheck), productTable.end());
}