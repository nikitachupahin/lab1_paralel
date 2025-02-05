#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

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

void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void compute(int** matrix, int size, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = i + 1; j < size; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void computeParallel(int** matrix, int size, int num_threads) {
    auto payload_begin = high_resolution_clock::now();
    vector<thread> threads;
    int segment_matrix = size / num_threads;
    int start = 0;

    for (int i = 0; i < num_threads; i++) {
        int end = (i == num_threads - 1) ? size : start + segment_matrix;
        threads.emplace_back(compute, matrix, size, start, end);
        start = end;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto payload_end = high_resolution_clock::now();
    auto elapsed = duration_cast<nanoseconds>(payload_end - payload_begin);
    printf("Payload Time: %.3f seconds.\n", elapsed.count() * 1e-9);
}

void computeNotParallel(int** matrix, int size) {
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

    int num_threads;
    cout << "Введіть кількість потоків: ";
    cin >> num_threads;

    int** matrix = allocMatrix(n);

    fillMatrix(matrix, n);

//    computeNotParallel(matrix, n);
    computeParallel(matrix, n, num_threads);

    deleteMatrix(matrix, n);

    return 0;
}