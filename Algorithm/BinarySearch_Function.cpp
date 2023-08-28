//ng<okのとき func(x)はng<x<aのときfalse、a<=x<okのときtrueを返す関数
//ok<ngのとき func(x)はok<x<=aのときtrue、a<x<ngのときfalseを返す関数
//二分探索してaの値を返す
//
//x,a,ng,ok はすべて整数型
//info... は関数funcの第2引数以降に追加で渡す情報(無くてもよい)
template <typename T, typename... Info>
T bsearch_int(bool (&func)(T, Info...), T ng, T ok, Info... info)
{
    T mid;
    while(ok - ng > 1 || ng - ok > 1)
    {
        mid = (ng + ok) / 2;
        if(func(mid, info...))
            ok = mid;
        else
            ng = mid;
    }
    return ok;
}

//関数funcの条件はbsearch_intと同様
//count回二分探索してaの近似値を返す(countが増えるほど誤差は減少 double型なら50回以上が適切)
//
//x,a,ng,ok はすべて小数型
//info... は関数funcの第2引数以降に追加で渡す情報(無くてもよい)
template <typename T, typename... Info>
T bsearch_double(bool (&func)(T, Info...), T ng, T ok, unsigned count, Info... info)
{
    T mid;
    while(count > 0)
    {
        mid = (ng + ok) / 2;
        if(func(mid, info...))
            ok = mid;
        else
            ng = mid;
        --count;
    }
    return ok;
}

/////

#include <iostream>
using namespace std;

int f(int x)
{
    return (x / 11) + 2 * (x / 13) + 3 * (x / 17) + 4 * (x / 23);
}

bool func(int x, int key)
{
    if(key <= f(x))
        return true;
    else
        return false;
}

int main(void)
{
    cout << "f(x) = floor(x/11) + 2*floor(x/13) + 3*floor(x/17) + 4*floor(x/23);\n";
    int key;
    while(true)
    {
        cin >> key;
        if(key < 0)
            return 0;
        
        int ret = bsearch_int(func, -1, 1000, key);
        cout << "f(" << ret - 1 << ")=" << f(ret - 1) << ", f(" << ret << ")=" << f(ret) << "\n";
    }
    return 0;
}
