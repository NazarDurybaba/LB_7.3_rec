#include <iostream>
#include <Windows.h>
using namespace std;

// ������� ��� �������� �������
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

// ������� ��� ������ �������
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

// �������� ������� ��� ���������� ������� �������� � �����
int rowProduct(int* row, int colCount, int j = 0, int product = 1) {
    return (j < colCount) ? ((row[j] >= 0) ? rowProduct(row, colCount, j + 1, product * row[j]) : -1) : product;
}

// ������� ��� ���������� ������� �������� � ������ ��� ��'����� ��������
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

// �������� ������� ��� ���������� ���� �������� �������
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

// ������� ��� ���������� ��������� ����� ��� �������� ���������
void maxDiagonalSum(int** a, const int rowCount, const int colCount, int l = 0, int maxSum = INT_MIN) {
    if (l < rowCount + colCount - 1) {
        int sum = diagonalSum(a, rowCount, colCount, l);
        maxSum = max(maxSum, sum);
        maxDiagonalSum(a, rowCount, colCount, l + 1, maxSum);
    }
    else {
        cout << "�������� ����� ��� �������� ���������: " << maxSum << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    int rowCount, colCount;
    cout << "������ ��������� ������� (rowCount x colCount): ";
    cin >> rowCount >> colCount;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        a[i] = new int[colCount];
    }
    Input(a, rowCount, colCount);
    cout << "������� �������: " << endl;
    Print(a, rowCount, colCount);
    cout << "������� �������� � ������ ��� ��'����� ��������: " << productOfPositiveRows(a, rowCount, colCount) << endl;
    maxDiagonalSum(a, rowCount, colCount);
    for (int i = 0; i < rowCount; i++) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}
