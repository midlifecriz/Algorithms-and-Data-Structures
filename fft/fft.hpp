#ifndef FFT_HPP
#define FFT_HPP


#include <iostream>
#include <vector>
#include <complex>


//Быстрое преобразование Фурье
template <typename T>
std::vector<std::complex<double>> FFT(std::vector<T> polynomial, std::complex<double> w) {
    size_t n = polynomial.size();
    if (n == 1) return {std::complex<double>(polynomial[0])};

    std::vector<T> AB[2];
    for (size_t i = 0; i < n; i++)
        AB[i % 2].push_back(polynomial[i]);

    auto A = FFT(AB[0], w*w);
    auto B = FFT(AB[1], w*w);

    std::vector<std::complex<double>> result(n);
    std::complex<double> wt = 1;
    size_t k = n/2;

    for (size_t j = 0; j < k; j++) {
        result[j] = A[j] + wt * B[j];
        result[j+k] = A[j] - wt * B[j];
        wt *= w;
    }
    return result;
}


//Обратное преобразование Фурье (интерполяция)
std::vector<int> interpolate(std::vector<std::complex<double>> polynomial) {
    size_t n = polynomial.size();
    const double pi = acos(-1);

    auto inv = FFT(polynomial, std::polar(1., -2 * pi / n));
    std::vector<int> result(n);

    for (size_t i = 0; i < n; i++)
        result[i] = round(real(inv[i]) / n);
    return result;
}


std::vector<int> FFT_polynomial_multiply(const std::vector<int>& a, const std::vector<int>& b) {
    size_t n = 1;
    while (n < a.size() + b.size() - 1)
        n <<= 1;

    std::vector<int> aa(a.begin(), a.end());
    std::vector<int> bb(b.begin(), b.end());
    aa.resize(n);
    bb.resize(n);

    auto A = FFT(aa, std::polar(1.0, 2 * acos(-1) / n));
    auto B = FFT(bb, std::polar(1.0, 2 * acos(-1) / n));

    for (size_t i = 0; i < n; i++)
        A[i] *= B[i];

    auto res = interpolate(A);
    res.resize(a.size() + b.size() - 1);
    return res;
}


std::vector<int> polynomial_multiply(const std::vector<int>& a, const std::vector<int>& b) {
    size_t n = a.size();
    size_t m = b.size();
    std::vector<int> result(n + m - 1, 0);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) 
            result[i + j] += a[i] + b[j];
    }

    return result;
}


#endif
