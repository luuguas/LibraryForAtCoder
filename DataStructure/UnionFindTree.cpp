//Union-Find木
//idxT: ノード番号の型
#include <vector>
template <typename idxT>
class UnionFind
{
private:
    idxT _group_count;
    std::vector<idxT> _parent, _size;
    
public:
    explicit UnionFind(void) {}
    explicit UnionFind(idxT size) {init(size);}
    void init(idxT size)
    {
        _group_count = size;
        _parent.assign(size, -1);
        _size.assign(size, 1);
    }

    idxT root(idxT node)
    {
        if(_parent[node] == -1)
            return node;
        else
            return _parent[node] = root(_parent[node]);
    }
    
    void unite(idxT node1, idxT node2)
    {
        idxT root1 = root(node1), root2 = root(node2);
        if(root1 == root2)
            return;
        
        if(_size[root1] < _size[root2])
        {
            _parent[root1] = root2;
            _size[root2] += _size[root1];
        }
        else
        {
            _parent[root2] = root1;
            _size[root1] += _size[root2];
        }
        --_group_count;
    }
    bool same(idxT node1, idxT node2) {return root(node1) == root(node2);}
    
    idxT size(idxT node) {return _size[root(node)];}
    idxT group_count(void) {return _group_count;}
};

/*
template <typename idxT>
class UnionFind
{
    //宣言 後にinit()で初期化
    explicit UnionFind(void);
    //ノード数を指定して初期化 各ノードを唯一の要素とするsize個の互いに素な集合を作成
    explicit UnionFind(idxT size);
    void init(idxT size);

    //nodeを含む集合の根を返す&経路圧縮
    idxT root(idxT node);
    
    //node1を含む集合とnode2を含む集合を併合する
    void unite(idxT node1, idxT node2);
    //node1とnode2が同じ集合に属しているならtrueを返す
    bool same(idxT node1, idxT node2);
    
    //nodeを含む集合の要素数を返す
    idxT size(idxT node);
    //集合の個数を返す
    idxT group_count(void);
};
*/

/////

#include <iostream>
#include <map>
using namespace std;
int main(void)
{
    UnionFind uf(10);
    
    int a, b;
    while(true)
    {
        map<int, vector<int>> disp;
        for(int i = 0; i < 10; ++i)
        {
            if(disp.find(uf.root(i)) == disp.end())
                disp[uf.root(i)] = vector<int>(1, i);
            else
                disp[uf.root(i)].emplace_back(i);
        }
        for(auto [key, value] : disp)
        {
            cout << "{";
            for(auto v : value)
            {
                cout << v <<", ";
            }
            cout << "\b\b}, ";
        }
        cout << "\b\b\n";
        
        cout << "command?(1:unite / 2:same / 3:size / 4:group_count / 9:end program): ";
        do
        {
            cin >> a;
        } while(a != 1 && a != 2 && a != 3 && a != 4 && a != 9);
        
        switch(a)
        {
        case 1:
            cout << "choose two nodes: ";
            cin >> a >> b;
            uf.unite(a, b);
            cout << "united " << a << " and " << b <<"\n\n";
            break;
            
        case 2:
            cout << "choose two nodes: ";
            cin >> a >> b;
            cout << a << " and " << b << " is ";
            if(!uf.same(a, b))
                cout << "not ";
            cout << "the same group\n\n";
            break;
            
        case 3:
            cout << "choose a node: ";
            cin >> a;
            cout << "size of group including " << a << " is " << uf.size(a) << "\n\n";
            break;
            
        case 4:
            cout << "number of groups is " << uf.group_count() << "\n\n";
            break;
            
        case 9:
            return 0;
        }
    }
}
