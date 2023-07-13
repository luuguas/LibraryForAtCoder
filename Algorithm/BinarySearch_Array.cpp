/* 昇順にソート済みのvector配列を二分探索 */

//keyに一致する要素のindex(添字)を返す
//一致する要素がなければ-1を返す
#include <vector>
template <typename T>
int bsearch(T key, const std::vector<T>& array)
{
    int left = -1, mid, right = (int)array.size();
    while(right - left > 1)
    {
        mid = (right + left) / 2;
        if(key == array[mid])
            return mid;
        else if(key < array[mid])
            right = mid;
        else
            left = mid;
    }
    return -1;
}       

//key以上を満たす要素のうち最小のindexを返す
//条件を満たす要素がなければarray.size()を返す
#include <vector>
template <typename T>
int geqmin(T key, const std::vector<T>& array)
{
    int left = -1, mid, right = (int)array.size();
    while(right - left > 1)
    {
        mid = (right + left) / 2;
        if(key <= array[mid])
            right = mid;
        else
            left = mid;
    }
    return right;
}

//key以下を満たす要素のうち最大のindexを返す
//条件を満たす要素がなければ-1を返す
#include <vector>
template <typename T>
int leqmax(T key, const std::vector<T>& array)
{
    int left = -1, mid, right = (int)array.size();
    while(right - left > 1)
    {
        mid = (right + left) / 2;
        if(key >= array[mid])
            left = mid;
        else
            right = mid;
    }
    return left;
}

/////

#include <iostream>
using namespace std;
int main(void)
{
    vector<int> a = {5, 9, 15, 21, 33, 37, 42, 48};
    cout << "array: {";
    for(int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << ", ";
    }
    cout << "}\n\n";
    
    cout << "bsearch / geqmin / leqmax\n";
    for(int key = 0; key <= 50; ++key)
    {
        cout << key << ": " << bsearch(key, a) <<" / " << geqmin(key, a) <<" / " << leqmax(key, a) << endl;
    }
    return 0;
}
