// 自然数nが素数かをtrue/falseで返す
template <typename T>
bool isPrime(T n) {
    if (n <= 1) return false;

    for (T d = 2; d * d <= n; ++d) {
        if (n % d == 0) return false;
    }

    return true;
}

// n以下の素数を配列で列挙する
#include <vector>
#include <cmath>
template <typename T>
std::vector<T> primes(T n) {
    if (n <= 1) { return std::vector<T>(0); }

    std::vector<T> ps;

    if (n > 100) { ps.reserve((T)(n / std::log(n))); }

    bool isPrime;
    for (T i = 2; i <= n; ++i) {
        isPrime = true;
        for (T &p : ps) {
            if (i % p == 0) {
                isPrime = false;
                break;
            }
            if (p * p > i) { break; }
        }
        if (isPrime) {
            ps.push_back(i);
        }
    }

    return ps;
}
