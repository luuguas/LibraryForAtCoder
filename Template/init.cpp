#include <bits/stdc++.h>
using namespace std;

#define stp(var, begin, end) for (auto var = begin; var < end; ++var)
#define stpe(var, begin, end) for (auto var = begin; var <= end; ++var)
#define stpd(var, begin, end) for (auto var = begin; var >= end; --var)

#define vec(type, name, ...) std::vector<type> name(__VA_ARGS__)
#define vec2(type, name, size1, ...) vec(std::vector<type>, name, size1, std::vector<type>(__VA_ARGS__))
#define vec3(type, name, size1, size2, ...) vec2(std::vector<type>, name, size1, size2, std::vector<type>(__VA_ARGS__))
#define all(array) std::begin(array), std::end(array)
#define rall(array) std::rbegin(array), std::rend(array)

void Yes(void) { std::cout << "Yes\n"; }
void No(void) { std::cout << "No\n"; }
bool YesNo(bool cond) { std::cout << (cond ? "Yes\n" : "No\n"); return cond; }

template <typename T>
bool chmin(T& var, const T& upd) { if (upd < var) { var = upd; return true; } return false; }
template <typename T>
bool chmax(T& var, const T& upd) { if (var < upd) { var = upd; return true; } return false; }

static const vector<vector<int>> _adj = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1}};
#define skip_grid(i, j, h, w) if (i < 0 || h <= i || j < 0 || w <= j) continue

using ll = long long;
static const long long MOD = 998244353ll, MOD2 = 1000000007ll;
static const long long INF_INT = 1ll << 30, INF_LL = 1ll << 62;
static const std::string _n = "\n", _s = " ";
#define re0 return 0

int main(void)
{
    
    return 0;
}
