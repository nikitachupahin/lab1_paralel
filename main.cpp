#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using chrono::nanoseconds;
using chrono::duration_cast;
using chrono::high_resolution_clock;

int** allocMatrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    return matrix;
}

void fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void compute(int** matrix, int size) {
    auto payload_begin = high_resolution_clock::now();
    for (int i = 0; i < size / 2; i++) {
        for (int j = i + 1; j < size; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    auto payload_end = high_resolution_clock::now();
    auto elapsed = duration_cast<nanoseconds>(payload_end - payload_begin);
    printf("Payload Time: %.3f seconds.\n", elapsed.count() * 1e-9);
}

int main() {
    srand(time(NULL));

    int n;
    cout << "Введіть розмір матриці: ";
    cin >> n;

    int** matrix = allocMatrix(n);

    fillMatrix(matrix, n);

    compute(matrix, n);

    deleteMatrix(matrix, n);

    return 0;
}