#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "fft.hpp"


#define SIZE    8


int main() {
    std::vector<int> a(SIZE);
    std::vector<int> b(SIZE);

    std::srand(static_cast<unsigned>(time(nullptr)));
    for (size_t i = 0; i < SIZE; i++) {
        a[i] = std::rand() % 100;
        b[i] = (std::rand() + i) % 100;
    }
    
    std::cout << "Многочлен a: ";
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';

    std::cout << "Многочлен b: ";
    for (int y : b) std::cout << y << ' ';
    std::cout << '\n';

    std::vector<int> fft_result = FFT_polynomial_multiply(a, b);

    std::cout << "FFT: ";
    for (int z : fft_result) std::cout << z << ' ';
    std::cout << '\n';

    std::vector<int> result = polynomial_multiply(a, b);

    std::cout << "Обычное умножение: ";
    for (int w : result) std::cout << w << ' ';
    std::cout << '\n';

    return 0;
}
