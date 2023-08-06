//最大流問題をFord-Fulkerson法で解くクラス
//idxT: グラフの添字の型 capT: 辺の最大流量の型
#include <vector>
#include <map>
template <typename idxT, typename capT>
class MaximumFlow
{
private:
    idxT _size;
    const std::vector<std::map<idxT, capT>>& _graph;
    capT _INF;
    std::vector<std::map<idxT, capT>> _rest, _flowed;
    std::vector<idxT> _visited;
    
    idxT _goal, _cnt;
    capT _total_flow;
    capT min(capT a, capT b)
    {
        if(a < b)
            return a;
        return b;
    }
    capT dfs(idxT now, capT flow)
    {
        if(now == _goal)
            return flow;
        
        _visited[now] = _cnt;
        for(auto& [next, cap] : _rest[now])
        {
            if(_visited[next] == _cnt)
                continue;
            if(cap == 0)
                continue;
            
            capT f = dfs(next, min(flow, cap));
            if(f > 0)
            {
                _rest[now][next] -= f;
                _flowed[next][now] += f;
                return f;
            }
        }
        for(auto& [next, cap] : _flowed[now])
        {
            if(_visited[next] == _cnt)
                continue;
            if(cap == 0)
                continue;
            
            capT f = dfs(next, min(flow, cap));
            if(f > 0)
            {
                _flowed[now][next] -= f;
                _rest[next][now] += f;
                return f;
            }
        }
        return 0;
    }
    
public:
    explicit MaximumFlow(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF) : _size(size), _graph(graph), _INF(INF) {}
    void solve(idxT start, idxT goal)
    {
        _rest = _graph;
        _flowed.assign(_size, std::map<idxT, capT>{});
        for(idxT i = 0; i < _size; ++i)
        {
            for(const auto& [j, cap] : _graph[i])
            {
                _flowed[j][i] = 0;
            }
        }
        _visited.assign(_size, -1);
        
        _total_flow = 0;
        _goal = goal;
        for(_cnt = 0;; ++_cnt)
        {
            capT flow = dfs(start, _INF);
            if(flow == 0)
                break;
            _total_flow += flow;
        }
    }
    capT total_flow(void) {return _total_flow;}
    capT vertex_flow(idxT idx)
    {
        if(idx == _goal)
            return _total_flow;
        capT flow = 0;
        for(const auto& [to, cap] : _graph[idx])
        {
            flow += _flowed[to][idx];
        }
        return flow;
    }
    capT edge_flow(idxT from, idxT to)
    {
        if(_graph[from].find(to) == _graph[from].end())
            return -1;
        return _flowed[to][from];
    }
};

/*
template <typename idxT, typename capT>
class MaximumFlow
{
    //頂点数、最大流量を重みにもつ有向グラフ、無限大(十分大きい値)を指定して初期化
    explicit MaximumFlow(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF);
    
    //頂点startから頂点goalに向けてフローを流したときの最大流量を求める
    void solve(idxT start, idxT goal);
    
    //!以下の関数はsolve()実行後に使用
    //頂点goalに流れ込む最大流量を返す
    capT total_flow(void);
    //頂点goalに流れこむ流量が最大になるときの、頂点idxを流れる流量を返す
    capT vertex_flow(idxT idx);
    //頂点goalに流れこむ流量が最大になるときの、頂点from-to間の辺を流れる流量を返す 辺が存在しない場合は-1を返す
    capT edge_flow(idxT from, idxT to);
};
*/
