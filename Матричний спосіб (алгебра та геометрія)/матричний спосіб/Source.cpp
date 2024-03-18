#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>

using namespace std;

void printMatrix(vector<vector<double>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//множення
vector<vector<double>> matrixMultiply(vector<vector<double>> A, vector<vector<double>> B) {
    vector<vector<double>> C(A.size(), vector<double>(B[0].size(), 0.0));

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printMatrix(C); cout << endl;
    return C;
}

//реверс
vector<vector<double>> inverseMatrix(vector<vector<double>> matrix) {
    vector<vector<double>> A = matrix;
    vector<vector<double>> I(matrix.size(), vector<double>(matrix.size(), 0.0));
    for (int i = 0; i < matrix.size(); i++) {
        I[i][i] = 1.0;
    }
    for (int j = 0; j < matrix.size(); j++) {
        int maxRow = j;
        for (int i = j + 1; i < matrix.size(); i++) {
            if (abs(A[i][j]) > abs(A[maxRow][j])) {
                maxRow = i;
            }
        }

        if (maxRow != j) {
            swap(A[j], A[maxRow]);
            swap(I[j], I[maxRow]);
        }

        double pivot = A[j][j];
        for (int k = j; k < matrix.size(); k++) {
            A[j][k] /= pivot;
        }
        for (int k = 0; k < matrix.size(); k++) {
            I[j][k] /= pivot;
        }

        for (int i = j + 1; i < matrix.size(); i++) {
            double factor = A[i][j];
            for (int k = j; k < matrix.size(); k++) {
                A[i][k] -= factor * A[j][k];
            }
            for (int k = 0; k < matrix.size(); k++) {
                I[i][k] -= factor * I[j][k];
            }
        }
    }

    for (int j = matrix.size() - 1; j >= 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            double factor = A[i][j];
            for (int k = j; k < matrix.size(); k++) {
                A[i][k] -= factor * A[j][k];
            }
            for (int k = 0; k < matrix.size(); k++) {
                I[i][k] -= factor * I[j][k];
            }
        }
    }

    // Output the inverse matrix
    printMatrix(I); cout << endl;

    return I;
}

//розв'язок
vector<double> solveLinearSystem(vector<vector<double>> A, vector<double> b) {
    vector<vector<double>> A_inv = inverseMatrix(A);
    vector<vector<double>> b_vec(b.size(), vector<double>(1));
    for (int i = 0; i < b.size(); i++) {
        b_vec[i][0] = b[i];
    }

    vector<vector<double>> x_vec = matrixMultiply(A_inv, b_vec);

    vector<double> x(x_vec.size());
    for (int i = 0; i < x_vec.size(); i++) {
        x[i] = round(x_vec[i][0] * 100) / 100;
    }

    return x;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //x+y+z=b
    vector<vector<double>> A = { {3, -2, -5, 1},
                                 {2, -3, 1, 5},
                                 {1, 2, 0, -4},
                                 {1, -1, -4, 9} };

    vector<double> b = { 3, -3, -3, 22 };

    vector<double> x = solveLinearSystem(A, b);

    for (int i = 0; i < x.size(); i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}
