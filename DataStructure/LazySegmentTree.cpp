//遅延評価セグメント木
//idxT: 添字の型 valT: 要素の値の型 updT: 更新情報の型
#include <vector>
template <typename idxT, typename valT, typename updT>
class LazySegmentTree
{
private:
    idxT _size, _tree_size, _leaf_head;
    std::vector<valT> _data;
    std::vector<updT> _lazy;
    
    valT (*_op)(valT, valT);
    valT _e;
    valT (*_mapping)(valT, updT);
    updT (*_composition)(updT, updT);
    updT _id;
    
    void init_inside(idxT size, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id)
    {
        _size = size, _op = op, _e = e, _mapping = mapping, _composition = composition, _id = id;
        
        _tree_size = 1;
        while(_tree_size < _size)
        {
            _tree_size *= 2;
        }
        _leaf_head = _tree_size - 1;
        _tree_size *= 2, _tree_size -= 1;
        
        _data.assign(_tree_size, e);
        _lazy.assign(_tree_size, id);
    }
    void build(void)
    {
        for(idxT i = _leaf_head - 1; i >= 0; --i)
        {
            _data[i] = _op(_data[2 * i + 1], _data[2 * i + 2]);
        }
    }
    
    void eval(idxT now)
    {
        if(_lazy[now] == _id)
            return;
        _data[now] = _mapping(_data[now], _lazy[now]);
        if(now < _leaf_head)
        {
            _lazy[2 * now + 1] = _composition(_lazy[2 * now + 1], _lazy[now]);
            _lazy[2 * now + 2] = _composition(_lazy[2 * now + 2], _lazy[now]);
        }
        _lazy[now] = _id;
    }
    
    idxT _l, _r;
    void update_inside(idxT L, idxT R, idxT now, updT f)
    {
        eval(now);
        if(R <= _l || _r <= L)
            return;
        else if(_l <= L && R <= _r)
        {
            _lazy[now] = _composition(_lazy[now], f);
            eval(now);
        }
        else
        {
            update_inside(L, (L + R) / 2, 2 * now + 1, f);
            update_inside((L + R) / 2, R, 2 * now + 2, f);
            _data[now] = _op(_data[2 * now + 1], _data[2 * now + 2]);
        }
    }
    
    valT query_inside(idxT L, idxT R, idxT now)
    {
        eval(now);
        if(R <= _l || _r <= L)
            return _e;
        else if(_l <= L && R <= _r)
            return _data[now];
        else
            return _op(query_inside(L, (L + R) / 2, 2 * now + 1), query_inside((L + R) / 2, R, 2 * now + 2));
    }
    
public:
    explicit LazySegmentTree(void) {}
    explicit LazySegmentTree(idxT size, valT val, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id) {init(size, val, op, e, mapping, composition, id);}
    explicit LazySegmentTree(const std::vector<valT>& array, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id) {init(array, op, e, mapping, composition, id);}
    void init(idxT size, valT val, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id)
    {
        init_inside(size, op, e, mapping, composition, id);
        if(val == e)
            return;
        for(idxT i = 0; i < _size; ++i)
        {
            _data[_leaf_head + i] = val;
        }
        build();
    }
    void init(const std::vector<valT>& array, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id)
    {
        init_inside((idxT)array.size(), op, e, mapping, composition, id);
        for(idxT i = 0; i < _size; ++i)
        {
            _data[_leaf_head + i] = array[i];
        }
        build();
    }
    
    void update(idxT i, updT f) {update(i, i + 1, f);}
    void update(idxT l, idxT r, updT f)
    {
        _l = l, _r = r;
        update_inside(0, _tree_size - _leaf_head, 0, f);
    }
    
    valT query(idxT i) {return query(i, i + 1);}
    valT query(idxT l, idxT r)
    {
        _l = l, _r = r;
        return query_inside(0, _tree_size - _leaf_head, 0);
    }
};

/*
//idxT: 添字の型 valT: 要素の値の型 updT: 更新情報の型
template <typename idxT, typename valT, typename updT>
class LazySegmentTree
{
    //宣言 後にinit()で初期化
    explicit LazySegmentTree(void);
    
    //要素数、初期値、評価関数、単位元、更新関数、更新合成関数、恒等更新情報 を指定して初期化
    explicit LazySegmentTree(idxT size, valT val, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id);
    void init(idxT size, valT val, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id);
    //配列、評価関数、単位元、更新関数、更新合成関数、恒等更新情報 を指定して初期化
    explicit LazySegmentTree(const std::vector<valT>& array, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id);
    void init(const std::vector<valT>& array, valT (*op)(valT, valT), valT e, valT (*mapping)(valT, updT), updT (*composition)(updT, updT), updT id);
    
    //!評価関数op(a, b): queryに使用する関数 / 結合法則 op(op(a, b), c) = op(a, op(b, c)) を満たす
    //!単位元e: 任意のaについて op(a, e) = op(e, a) = a を満たす値
    //!更新関数mapping(a, f): aを更新情報fをもとに更新した結果を返す関数 / 分配法則 mapping(op(a, b), f) = op(mapping(a, f), mapping(b, f)) を満たす
    //!更新合成関数composition(f, g): ある値をfをもとに更新しさらにgをもとに更新する操作と等しい操作を表す更新情報を返す関数
    // すなわち、任意のaについて mapping(mapping(a, f), g) = mapping(a, composition(f, g)) を満たす
    //!恒等更新情報id: ある値をidをもとに更新した結果が元の値と等しいような更新情報
    // すなわち、任意のaについて mapping(a, id) = a を満たす
    
    //i番目の要素を更新情報fをもとに更新する
    void update(idxT i, updT f);
    //区間[l, r)の全ての要素 A[l], A[l + 1], ..., A[r - 1] を更新情報fをもとに更新する
    void update(idxT l, idxT r, updT f);
    
    //i番目の要素を返す
    valT query(idxT i);
    //区間[l, r)に対するopの評価 op(A[l], A[l + 1], ..., A[r - 1]) を返す
    valT query(idxT l, idxT r);
};
*/

/////

//区間変更・区間最小値取得の場合
using idxT = int;
using valT = long long;
using updT = long long;
valT op(valT a, valT b) {return std::min(a, b);}
valT e = 1ll << 62;
updT id = 1ll << 62;
valT mapping(valT a, updT f) {return (f == id ? a : f);}
updT composition(updT f, updT g) {return (g == id ? f : g);}

//区間加算・区間最小値取得の場合
/*
using idxT = int;
using valT = long long;
using updT = long long;
valT op(valT a, valT b) {return std::min(a, b);}
valT e = 1ll << 62;
valT mapping(valT a, updT f) {return a + f;}
updT composition(updT f, updT g) {return f + g;}
updT id = 0;
*/

//区間変更・区間最大値取得の場合
/*
using idxT = int;
using valT = long long;
using updT = long long;
valT op(valT a, valT b) {return std::max(a, b);}
valT e = -1ll << 62;
updT id = -1ll << 62;
valT mapping(valT a, updT f) {return (f == id ? a : f);}
updT composition(updT f, updT g) {return (g == id ? f : g);}
*/

//区間加算・区間最大値取得の場合
/*
using idxT = int;
using valT = long long;
using updT = long long;
valT op(valT a, valT b) {return std::max(a, b);}
valT e = -1ll << 62;
updT id = 0;
valT mapping(valT a, updT f) {return a + f;}
updT composition(updT f, updT g) {return f + g;}
*/

//区間変更・区間和取得の場合
/*
using idxT = int;
struct valT
{
    long long val;
    idxT size;
    bool operator==(valT other) {return val == other.val && size == other.size;}
};
using updT = long long;
valT op(valT a, valT b) {return valT{a.val + b.val, a.size + b.size};}
valT e = valT{0, 0};
updT id = 1ll << 62;
valT mapping(valT a, updT f) {return (f == id ? a : valT{f * a.size, a.size});}
updT composition(updT f, updT g) {return (g == id ? f : g);}
*/

//区間加算・区間和取得の場合
/*
using idxT = int;
struct valT
{
    long long val;
    idxT size;
    bool operator==(valT other) {return val == other.val && size == other.size;}
};
using updT = long long;
valT op(valT a, valT b) {return valT{a.val + b.val, a.size + b.size};}
valT e = valT{0, 0};
valT mapping(valT a, updT f) {return valT{a.val + f * a.size, a.size};}
updT composition(updT f, updT g) {return f + g;}
updT id = 0;
*/

#include <iostream>
using namespace std;
int main(void)
{
    int N;
    cout << "Input the length of array: ";
    cin >> N;
    
    LazySegmentTree<idxT, valT, updT> seg(N, 0, op, e, mapping, composition, id);
    
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
            cout << "Input range[l, r) and new value: ";
            cin >> a >> b >> c;
            seg.update(a, b, c);
            cout << "Updated A[" << a << ", " << b << ") with " << c <<"\n\n";
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
