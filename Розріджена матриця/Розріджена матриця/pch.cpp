//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <list>
#include <windows.h>

using namespace std;

class SparseMatrix {
private:
    list<list<int>> matrix;
    int rows;
    int cols;

public:
    SparseMatrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        for (int i = 0; i < rows; i++) {
            matrix.push_back(list<int>(cols, 0));
        }
    }

    void addElement(int row, int col, int value) {                       //пошук елементу у матриц≥
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "\n[ ERROR ] ≈лементу не знайдено." << endl;
            return;
        }

        auto row_it = matrix.begin();                                     //пошук р€дку, стовпц€, дод. елем
        advance(row_it, row);

        auto col_it = row_it->begin();
        advance(col_it, col);

        *col_it = value;
    }

    int getElement(int row, int col) {                                   //пошук елементу у матриц≥
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "\n[ ERROR ] ≈лементу не знайдено." << endl;
            return 0;
        }

        auto row_it = matrix.begin();
        advance(row_it, row);

        auto col_it = row_it->begin();
        advance(col_it, col);

        return *col_it;
    }

    void removeElement(int row, int col) {                                //пошук елементу у матриц≥
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "\n[ ERROR ] ≈лементу не знайдено." << endl;
            return;
        }
                                    
        auto row_it = matrix.begin();                                     //пошук р€дку, стовпц€; видал€Їмо, €кщо ≥нсуЇ
        advance(row_it, row);

        auto col_it = row_it->begin();
        advance(col_it, col);

        *col_it = 0;
    }

    void replaceElement(int row, int col, int value) {                    //пошук елементу у матриц≥
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "\n[ ERROR ] ≈лементу не знайдено." << endl;
            return;
        }

        auto row_it = matrix.begin();                                     //пошук р€дку, стовпц€; зам≥н€Їмо, €кщо ≥нсуЇ
        advance(row_it, row);

        auto col_it = row_it->begin();
        advance(col_it, col);

        *col_it = value;
    }

    void display() {
        cout << "\n–озр≥джена матриц€:" << endl;
        for (auto row_it = matrix.begin(); row_it != matrix.end(); row_it++) {
            for (auto col_it = row_it->begin(); col_it != row_it->end(); col_it++) {
                cout << *col_it << "\t";
            }
            cout << endl;
        }

        cout << "\nў≥льна матриц€:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                auto row_it = matrix.begin();                            //знаходимо р€док
                for (int k = 0; k < i; k++) {                            //чи знаходитьс€ ≥тератор в к≥нц≥ списку
                    if (row_it == matrix.end()) {
                        break;
                    }
                    row_it++;
                }

                auto col_it = row_it->begin();                           //аналог≥чно з стовпц€ми
                for (int k = 0; k < j; k++) {
                    if (col_it == row_it->end()) {
                        break;
                    }
                    col_it++;
                }

                if (col_it != row_it->end() && *col_it != 0) {           //пошук ненульового
                    cout << *col_it << " (" << i << ", " << j << ")" << endl;
                }
            }
        }
    }

};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SparseMatrix matrix(3, 3);

    matrix.addElement(0, 0, 1);
    matrix.addElement(0, 2, 2);
    matrix.addElement(1, 1, 3);
    matrix.addElement(2, 0, 4);
    matrix.addElement(2, 2, 5);

    matrix.display(); cout << "_________________" << endl;

    matrix.removeElement(1, 1);

    matrix.display(); cout << "_________________" << endl;

    matrix.replaceElement(2, 2, 6);

    matrix.display(); cout << "_________________" << endl;

    return 0;
}



TEST(SparseMatrixTest, AddElement) {
    SparseMatrix matrix(3, 3);

    matrix.addElement(0, 0, 1);
    matrix.addElement(0, 2, 2);
    matrix.addElement(1, 1, 3);
    matrix.addElement(2, 0, 4);
    matrix.addElement(2, 2, 5);

    EXPECT_EQ(matrix.getElement(0, 0), 1);
    EXPECT_EQ(matrix.getElement(0, 2), 2);
    EXPECT_EQ(matrix.getElement(1, 1), 3);
    EXPECT_EQ(matrix.getElement(2, 0), 4);
    EXPECT_EQ(matrix.getElement(2, 2), 5);
}

TEST(SparseMatrixTest, RemoveElement) {
    SparseMatrix matrix(3, 3);

    matrix.addElement(0, 0, 1);
    matrix.addElement(0, 2, 2);
    matrix.addElement(1, 1, 3);
    matrix.addElement(2, 0, 4);
    matrix.addElement(2, 2, 5);

    matrix.removeElement(1, 1);

    EXPECT_EQ(matrix.getElement(1, 1), 0);
}

TEST(SparseMatrixTest, ReplaceElement) {
    SparseMatrix matrix(3, 3);

    matrix.addElement(0, 0, 1);
    matrix.addElement(0, 2, 2);
    matrix.addElement(1, 1, 3);
    matrix.addElement(2, 0, 4);
    matrix.addElement(2, 2, 5);

    matrix.replaceElement(2, 2, 6);

    EXPECT_EQ(matrix.getElement(2, 2), 6);
}

TEST(SparseMatrixTest, InvalidRow) {
    SparseMatrix matrix(3, 3);

    testing::internal::CaptureStdout();
    matrix.addElement(3, 0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("\n[ ERROR ] ≈лементу не знайдено.\n", output);
}


TEST(SparseMatrixTest, InvalidCol) {
    SparseMatrix matrix(3, 3);

    testing::internal::CaptureStdout();
    matrix.addElement(0, 3, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("\n[ ERROR ] ≈лементу не знайдено.\n", output);
}
