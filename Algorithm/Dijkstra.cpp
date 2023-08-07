//重み付きグラフの最短経路長をダイクストラ法で解くクラス
//idxT: グラフの頂点番号の型 wtT: 辺の重みの型
#include <vector>
#include <map>
#include <queue>
template <typename idxT, typename wtT>
class Dijkstra
{
private:
    idxT _size;
    std::vector<std::map<idxT, wtT>> _graph;
    wtT _INF;
    std::vector<wtT> _dist;
    std::vector<idxT> _prev;
    
public:
    explicit Dijkstra(void) {}
    explicit Dijkstra(idxT size, const std::vector<std::map<idxT, wtT>>& graph, wtT INF) {init(size, graph, INF);}
    void init(idxT size, const std::vector<std::map<idxT, wtT>>& graph, wtT INF)
    {
        _size = size;
        _graph = graph;
        _INF = INF;
    }
    void solve(idxT start)
    {
        _dist.assign(_size, _INF);
        _prev.assign(_size, -2);
        std::priority_queue<std::pair<wtT, idxT>, std::vector<std::pair<wtT, idxT>>, std::greater<std::pair<wtT, idxT>>> pque;
        
        _dist[start] = 0;
        _prev[start] = -1;
        pque.push(std::pair<wtT, idxT>{0, start});
        while(!pque.empty())
        {
            auto [now_dist, now_idx] = pque.top();
            pque.pop();
            
            if(_dist[now_idx] < now_dist)
                continue;
            
            for(auto& [next_idx, next_wt] : _graph[now_idx])
            {
                if(_dist[now_idx] + next_wt < _dist[next_idx])
                {
                    _dist[next_idx] = _dist[now_idx] + next_wt;
                    _prev[next_idx] = now_idx;
                    pque.push(std::pair<wtT, idxT>{_dist[next_idx], next_idx});
                }
            }
        }
    }
    wtT dist(idxT idx) {return _dist[idx];}
    std::vector<wtT> dist_all(void) {return _dist;}
    idxT prev(idxT idx) {return _prev[idx];}
    std::vector<idxT> prev_all(void) {return _prev;}
};

/*
template <typename idxT, typename wtT>
class Dijkstra
{
    //宣言 後にinit()で初期化
    explicit Dijkstra(void);
    //頂点数、重み付きグラフ、無限大(十分大きい値)を指定して初期化
    explicit Dijkstra(idxT size, const std::vector<std::map<idxT, wtT>>>& graph, wtT INF);
    void init(idxT size, const std::vector<std::map<idxT, wtT>>& graph, wtT INF);
    
    //頂点から各頂点までの最短経路長を求める
    void solve(idxT start);
    
    //!以下の関数はsolve()実行後に使用
    //頂点start-idx間の最短経路長を返す 経路が存在しない場合はINFを返す
    wtT dist(idxT idx);
    //頂点startから全頂点への最短経路長を配列で返す
    std::vector<wtT> dist_all(void);
    //頂点start-idx間の最短経路を示す有向パスにおいて、頂点idxの1つ前の頂点を返す 頂点idxが頂点startに等しい場合は-1、経路が存在しない場合は-2を返す
    idxT prev(idxT idx);
    //全頂点のprev()を配列で返す
    std::vector<idxT> prev_all(void);
};
*/
