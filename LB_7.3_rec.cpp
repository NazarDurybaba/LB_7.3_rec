#include <iostream>
#include <Windows.h>
using namespace std;

// Функція для введення матриці
void Input(int** a, const int rowCount, const int colCount, int i = 0, int j = 0) {
    if (i < rowCount) {
        if (j < colCount) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
            Input(a, rowCount, colCount, i, j + 1);
        }
        else {
            Input(a, rowCount, colCount, i + 1, 0);
        }
    }
}

// Функція для виводу матриці
void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0) {
    if (i < rowCount) {
        if (j < colCount) {
            cout << a[i][j] << " ";
            Print(a, rowCount, colCount, i, j + 1);
        }
        else {
            cout << endl;
            Print(a, rowCount, colCount, i + 1, 0);
        }
    }
}

// Допоміжна функція для обчислення добутку елементів у рядку
int rowProduct(int* row, int colCount, int j = 0, int product = 1) {
    return (j < colCount) ? ((row[j] >= 0) ? rowProduct(row, colCount, j + 1, product * row[j]) : -1) : product;
}

// Функція для обчислення добутку елементів у рядках без від'ємних елементів
int productOfPositiveRows(int** a, const int rowCount, const int colCount, int i = 0, int product = 1) {
    if (i < rowCount) {
        int rowProd = rowProduct(a[i], colCount);
        if (rowProd != -1) {
            product *= rowProd;
        }
        return productOfPositiveRows(a, rowCount, colCount, i + 1, product);
    }
    return product;
}

// Допоміжна функція для обчислення суми елементів діагоналі
int diagonalSum(int** a, const int rowCount, const int colCount, int l, int i = 0, int sum = 0) {
    if (i < rowCount) {
        int j = l - i;
        if (j >= 0 && j < colCount) {
            sum += a[i][j];
        }
        return diagonalSum(a, rowCount, colCount, l, i + 1, sum);
    }
    return sum;
}

// Функція для обчислення максимуму серед сум елементів діагоналей
void maxDiagonalSum(int** a, const int rowCount, const int colCount, int l = 0, int maxSum = INT_MIN) {
    if (l < rowCount + colCount - 1) {
        int sum = diagonalSum(a, rowCount, colCount, l);
        maxSum = max(maxSum, sum);
        maxDiagonalSum(a, rowCount, colCount, l + 1, maxSum);
    }
    else {
        cout << "Максимум серед сум елементів діагоналей: " << maxSum << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    int rowCount, colCount;
    cout << "Введіть розмірність матриці (rowCount x colCount): ";
    cin >> rowCount >> colCount;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        a[i] = new int[colCount];
    }
    Input(a, rowCount, colCount);
    cout << "Введена матриця: " << endl;
    Print(a, rowCount, colCount);
    cout << "Добуток елементів у рядках без від'ємних елементів: " << productOfPositiveRows(a, rowCount, colCount) << endl;
    maxDiagonalSum(a, rowCount, colCount);
    for (int i = 0; i < rowCount; i++) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}
