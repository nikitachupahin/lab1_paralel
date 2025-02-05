#include <iostream>
#include <chrono>

using std::chrono::nanoseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

void someFunction() {
    int sum = 0;
    for (int i = 0; i < 1000000000; ++i) {
        sum += i;
    }
}

int main() {
    auto start = high_resolution_clock::now();
    someFunction();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);

    std::cout << "Execution time: " << duration.count() * 1e-9 << " seconds" << std::endl;
    return 0;
}