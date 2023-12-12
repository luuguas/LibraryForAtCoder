//セグメント木
//idxT: 添字の型 valT: 要素の値の型
#include <vector>
template <typename idxT, typename valT>
class SegmentTree
{
private:
    idxT _size, _tree_size, _leaf_head;
    std::vector<valT> _data;
    
    valT (*_op)(valT, valT);
    valT _e;
    
    void init_inside(idxT size, valT (*op)(valT, valT), valT e)
    {
        _size = size, _op = op, _e = e;
        
        _tree_size = 1;
        while(_tree_size < _size)
        {
            _tree_size *= 2;
        }
        _leaf_head = _tree_size - 1;
        _tree_size *= 2, _tree_size -= 1;
        
        _data.assign(_tree_size, e);
    }
    void build(void)
    {
        for(idxT i = _leaf_head - 1; i >= 0; --i)
        {
            _data[i] = _op(_data[2 * i + 1], _data[2 * i + 2]);
        }
    }
    
    idxT _l, _r;
    valT query_inside(idxT L, idxT R, idxT now)
    {
        if(R <= _l || _r <= L)
            return _e;
        else if(_l <= L && R <= _r)
            return _data[now];
        else
            return _op(query_inside(L, (L + R) / 2, 2 * now + 1), query_inside((L + R) / 2, R, 2 * now + 2));
    }
    
public:
    explicit SegmentTree(void) {}
    explicit SegmentTree(idxT size, valT val, valT (*op)(valT, valT), valT e) {init(size, val, op, e);}
    explicit SegmentTree(const std::vector<valT>& array, valT (*op)(valT, valT), valT e) {init(array, op, e);}
    void init(idxT size, valT val, valT (*op)(valT, valT), valT e)
    {
        init_inside(size, op, e);
        if(val == e)
            return;
        for(idxT i = 0; i < _size; ++i)
        {
            _data[_leaf_head + i] = val;
        }
        build();
    }
    void init(const std::vector<valT>& array, valT (*op)(valT, valT), valT e)
    {
        init_inside((idxT)array.size(), op, e);
        for(idxT i = 0; i < _size; ++i)
        {
            _data[_leaf_head + i] = array[i];
        }
        build();
    }
    
    void update(idxT i, valT val)
    {
        idxT now = _leaf_head + i;
        _data[now] = val;
        
        idxT parent;
        while(now > 0)
        {
            parent = (now - 1) / 2;
            _data[parent] = _op(_data[2 * parent + 1], _data[2 * parent + 2]);
            now = parent;
        }
    }
    
    valT query(idxT i) {return _data[_leaf_head + i];}
    valT query(idxT l, idxT r)
    {
        _l = l, _r = r;
        return query_inside(0, _tree_size - _leaf_head, 0);
    }
};

/*
//idxT: 添字の型 valT: 要素の値の型
template <typename idxT, typename valT>
class SegmentTree
{
    //宣言 後にinit()で初期化
    explicit SegmentTree(void);
    
    //要素数、初期値、評価関数、単位元を指定して初期化
    explicit SegmentTree(idxT size, valT val, valT (*op)(valT, valT), valT e);
    void init(idxT size, valT val, valT (*op)(valT, valT), valT e);
    //配列、評価関数、単位元を指定して初期化
    explicit SegmentTree(const std::vector<valT>& array, valT (*op)(valT, valT), valT e);
    void init(const std::vector<valT>& array, valT (*op)(valT, valT), valT e);
    
    //!評価関数op(a, b): queryに使用する関数 / 結合法則 op(op(a, b), c) = op(a, op(b, c)) を満たす
    //!単位元e: 任意のaについて op(a, e) = op(e, a) = a を満たす値
    
    //i番目の要素をvalに更新する
    void update(idxT i, valT val);
    
    //i番目の要素を返す
    valT query(idxT i);
    //区間[l, r)に対するopの評価 op(A[l], A[l + 1], ..., A[r - 1]) を返す
    valT query(idxT l, idxT r);
};
*/

/////

//区間最小値を取得する場合(RMQ)
using idxT = int;
using valT = long long;
valT op(valT a, valT b) {return std::min(a, b);}
valT e = 1ll << 62;

//区間最大値を取得する場合(RMQ)
/*
using idxT = int;
using valT = long long;
valT op(valT a, valT b) {return std::max(a, b);}
valT e = -1ll << 62;
*/

//区間和を取得する場合(RSQ)
/*
using idxT = int;
using valT = long long;
valT op(valT a, valT b) {return a + b;}
valT e = 0;
*/

#include <iostream>
using namespace std;
int main(void)
{
    int N;
    cout << "Input the length of array: ";
    cin >> N;
    
    SegmentTree<idxT, valT> seg(N, 0, op, e);
    
    int a, b;
    long long c;
    while(true)
    {
        cout << "command?(1:update / 2:query / 9:end program): ";
        do
        {
            cin >> a;
        }while(a != 1 && a != 2 && a != 9);
        
        switch(a)
        {
        case 1:
            cout << "Input index and new value: ";
            cin >> a >> c;
            seg.update(a, c);
            cout << "Updated A[" << a << "] with " << c <<"\n\n";
            break;
            
        case 2:
            cout << "Input range[l, r): ";
            cin >> a >> b;
            cout << "Minimum of A[" << a << ", " << b << ") is " << seg.query(a, b) << "\n\n";
            break;
            
        case 9:
            return 0;
        }
    }
}
