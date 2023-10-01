//セグメント木
//idxT: サイズの型 valT: 要素の値の型
#include <vector>
template <typename idxT, typename valT>
class SegmentTree
{
private:
    idxT _size, _tree_size, _head;
    std::vector<valT> _tree;
    valT _ID;
    valT (*_calc)(valT a, valT b);
    
    void build(void)
    {
        for(idxT i = _head - 1; i >= 0; --i)
        {
            _tree[i] = _calc(_tree[2 * i + 1], _tree[2 * i + 2]);
        }
    }
    idxT _l, _r;
    valT query_inside(idxT L, idxT R, idxT now)
    {
        if(R <= _l || _r <= L)
            return _ID;
        else if(_l <= L && R <= _r)
            return _tree[now];
        else
            return _calc(query_inside(L, (L + R) / 2, 2 * now + 1), query_inside((L + R) / 2, R, 2 * now + 2));
    }
    
public:
    explicit SegmentTree(void) {}
    explicit SegmentTree(idxT size, valT ID, valT (*calc)(valT a, valT b)) {init(size, ID, calc);}
    explicit SegmentTree(const std::vector<valT> &array, valT ID, valT (*calc)(valT a, valT b)) {init(array, ID, calc);}
    void init(idxT size, valT ID, valT (*calc)(valT a, valT b))
    {
        _size = size;
        _ID = ID;
        _calc = calc;
        
        _tree_size = 1;
        while(_tree_size < _size)
        {
            _tree_size *= 2;
        }
        _head = _tree_size - 1;
        _tree_size *= 2, _tree_size -= 1;
        _tree.assign(_tree_size, _ID);
    }
    void init(const std::vector<valT> &array, valT ID, valT (*calc)(valT a, valT b))
    {
        init((idxT)array.size(), ID, calc);
        for(idxT i = 0; i < _size; ++i)
        {
            _tree[_head + i] = array[i];
        }
        build();
    }
    const valT& operator[](idxT idx) {return _tree[_head + idx];}
    void update(idxT idx, valT val)
    {
        _tree[_head + idx] = val;
        idx += _head;
        
        idxT parent;
        while(idx > 0)
        {
            parent = (idx - 1) / 2;
            _tree[parent] = _calc(_tree[2 * parent + 1], _tree[2 * parent + 2]);
            idx = parent;
        }
    }
    valT query(idxT l, idxT r)
    {
        _l = l, _r = r;
        return query_inside(0, _tree_size - _head, 0);
    }
};

/*
template <typename idxT, typename valT>
class SegmentTree
{
    //宣言 後にinit()で初期化
    explicit SegmentTree(void);
    
    //単位元は任意のaについて calc(a, ID) = calc(ID, a) = a を満たす
    //評価関数は結合法則 calc(calc(a, b), c) = calc(a, calc(b, c)) を満たす
    
    //サイズ、単位元、評価関数を指定して初期化
    explicit SegmentTree(idxT size, valT ID, valT (*calc)(valT a, valT b));
    void init(idxT size, valT ID, valT (*calc)(valT a, valT b));
    //要素の初期値を表す配列、単位元、評価関数を指定して初期化
    explicit SegmentTree(const std::vector<valT> &array, valT ID, valT (*calc)(valT a, valT b));
    void init(const std::vector<valT> &array, valT ID, valT (*calc)(valT a, valT b));
    
    //idx番目の要素の値を返す(変更不可)
    const valT& operator[](idxT idx);
    //idx番目の要素をvalに更新する
    void update(idxT idx, valT val);
    //区間[l, r)に対するcalc関数の評価を返す
    valT query(idxT l, idxT r);
};
*/
