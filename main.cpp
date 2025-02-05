#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using chrono::nanoseconds;
using chrono::duration_cast;
using chrono::high_resolution_clock;

void fillAndDisplayMatrix(int N) {
    int matrix[N][N];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    cout << "Матриця:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nМатриця, відображена симетрично:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(NULL));

    int n = 0;
    cout << "Введи розмір матриці: ";
    cin >> n;

    auto start = high_resolution_clock::now();
    fillAndDisplayMatrix(n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "\nЧас виконання: " << duration.count() * 1e-6 << " мілісекунд" << endl;

    return 0;
}
