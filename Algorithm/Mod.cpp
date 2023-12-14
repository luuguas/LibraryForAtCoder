//法MODにおける四則演算・累乗・組み合わせnCrを求める関数たち
//!引数a, bは 0 <= a < MOD, 0 <= b < MOD を満たす

//a + b
long long mod_add(long long a, long long b, long long MOD) {return (a + b) % MOD;}

//a - b
long long mod_sub(long long a, long long b, long long MOD)
{
    a = (a - b) % MOD;
    if(a < 0)
        a += MOD;
    return a;
}

//a * b
long long mod_mul(long long a, long long b, long long MOD) {return (a * b) % MOD;}

//1 / a (a, MODは互いに素)
long long mod_inv(long long a, long long MOD) {
    long long b = MOD, c = 1, d = 0, g;
    while (b != 0) {
        g = c - a / b * d, c = d, d = g;
        g = a % b, a = b, b = g;
    }
    return (c + MOD) % MOD;
}

//a / b (b, MODは互いに素)
long long mod_inv(long long a, long long b, long long MOD) {
    long long aa = a;
    long long a = b, b = MOD, c = 1, d = 0, g;
    while (b != 0) {
        g = c - a / b * d, c = d, d = g;
        g = a % b, a = b, b = g;
    }
    c += MOD, c %= MOD;
    return aa * c % MOD;
}

//a ^ p (0 <= p)
long long mod_pow(long long a, long long p, long long MOD)
{
    if (a == 0)
        return 0;
    long long a_2n = a, pow = p, a_p = 1;
    while (pow > 0)
    {
        if (pow % 2 == 1)
            a_b *= a_2n, a_p %= MOD;
        a_2n *= a_2n, a_2n %= MOD;
        pow /= 2;
    }
    return a_p;
}

//法MODにおける組み合わせの総数nCrを求めるクラス
//T: 値の型
#include <vector>
template <typename T>
class ncr_mod
{
private:
    T _max, _MOD;
    vector<T> _fac, _finv, _inv;

public:
    explicit ncr_mod(T max, T MOD) : _max(max), _MOD(MOD)
    {
        _fac.assign(_max + 1, 0), _fac[0] = 1, _fac[1] = 1;
        _finv.assign(_max + 1, 0), _finv[0] = 1, _finv[1] = 1;
        _inv.assign(_max + 1, 0), _inv[1] = 1;
        for (T i = 2; i <= _max; ++i)
        {
            _fac[i] = _fac[i - 1] * i % _MOD;
            _inv[i] = _MOD - _inv[_MOD % i] * (_MOD / i) % _MOD;
            _finv[i] = _finv[i - 1] * _inv[i] % _MOD;
        }
        return;
    };
    
    T operator()(T n, T r)
    {
        if (_max < n || n < r)
            return -1;
        return _fac[n] * (_finv[r] * _finv[n - r] % _MOD) % _MOD;
    }
};

/*
template <typename T>
class ncr_mod
{
    //n, rの最大値、法を指定して初期化
    //!法MODは素数
    explicit ncr_mod(T max, T MOD);
    
    //n個からr個を重複なく選ぶ組み合わせの総数nCrをMODで割ったあまりを返す
    T operator()(T n, T r);
};
*/
