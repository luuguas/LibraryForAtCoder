//最大流問題をDinic法で解くクラス
//idxT: グラフの頂点番号の型 capT: 辺の最大流量の型
#include <vector>
#include <queue>
#include <map>
template <typename idxT, typename capT>
class MaximumFlow
{
private:
    idxT _size;
    std::vector<std::map<idxT, capT>> _graph;
    capT _INF;
    std::vector<std::map<idxT, capT>> _rest, _flowed;
    std::vector<idxT> _visited;
    std::vector<idxT> _level;
    
    idxT _goal, _cnt;
    capT _flow_total;
    capT min(const capT& a, const capT& b)
    {
        if(a < b)
            return a;
        return b;
    }
    void bfs(idxT start)
    {
        _level.assign(_size, -1);
        std::queue<idxT> que;
        _level[start] = 0;
        que.push(start);
        while(!que.empty())
        {
            idxT now = que.front();
            que.pop();
            for(auto& [next, cap] : _rest[now])
            {
                if(_level[next] == -1 && cap > 0)
                {
                    _level[next] = _level[now] + 1;
                    que.push(next);
                }
            }
            for(auto& [next, cap] : _flowed[now])
            {
                if(_level[next] == -1 && cap > 0)
                {
                    _level[next] = _level[now] + 1;
                    que.push(next);
                }
            }
        }
    }
    capT dfs(idxT now, capT flow)
    {
        if(now == _goal)
            return flow;
        
        _visited[now] = _cnt;
        for(auto& [next, cap] : _rest[now])
        {
            if(_visited[next] < _cnt && cap > 0 && _level[now] < _level[next])
            {
                capT f = dfs(next, min(flow, cap));
                if(f > 0)
                {
                    cap -= f;
                    _flowed[next][now] += f;
                    return f;
                }
            }
        }
        for(auto& [next, cap] : _flowed[now])
        {
            if(_visited[next] < _cnt && cap > 0 && _level[now] < _level[next])
            {
                capT f = dfs(next, min(flow, cap));
                if(f > 0)
                {
                    cap -= f;
                    _flowed[next][now] += f;
                    return f;
                }
            }
        }
        return 0;
    }
    
public:
    explicit MaximumFlow(void) {}
    explicit MaximumFlow(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF) {init(size, graph, INF);}
    void init(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF)
    {
        _size = size;
        _graph = graph;
        _INF = INF;
    }
    void solve(idxT start, idxT goal)
    {
        _rest = _graph;
        _flowed.assign(_size, std::map<idxT, capT>{});
        for(idxT i = 0; i < _size; ++i)
        {
            for(auto& [j, cap] : _graph[i])
            {
                _flowed[j][i] = 0;
            }
        }
        
        _flow_total = 0;
        _goal = goal;
        while(true)
        {
            bfs(start);
            if(_level[goal] == -1)
                break;
            _visited.assign(_size, -1);
            for(_cnt = 0;; ++_cnt)
            {
                capT flow = dfs(start, _INF);
                if(flow == 0)
                    break;
                _flow_total += flow;
            }
        }
    }
    capT flow_total(void) {return _flow_total;}
    capT flow_vertex(idxT idx)
    {
        if(idx == _goal)
            return _flow_total;
        capT flow = 0;
        for(auto& [to, cap] : _graph[idx])
        {
            flow += _flowed[to][idx];
        }
        return flow;
    }
    capT flow_edge(idxT from, idxT to)
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
    //宣言 後にinit()で初期化
    explicit MaximumFlow(void);
    //頂点数、最大流量を重みにもつ有向グラフ、無限大(十分大きい値)を指定して初期化
    explicit MaximumFlow(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF);
    void init(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF);
    
    //頂点startから頂点goalに向けてフローを流したときの最大流量を求める
    void solve(idxT start, idxT goal);
    
    //!以下の関数はsolve()実行後に使用
    //頂点goalに流れ込む最大流量を返す
    capT flow_total(void);
    //頂点goalに流れこむ流量が最大になるときの、頂点idxを流れる流量を返す
    capT flow_vertex(idxT idx);
    //頂点goalに流れこむ流量が最大になるときの、頂点from-to間の辺を流れる流量を返す 辺が存在しない場合は-1を返す
    capT flow_edge(idxT from, idxT to);
};
*/

//最大流問題をFord-Fulkerson法で解くクラス
//idxT: グラフの頂点番号の型 capT: 辺の最大流量の型
#include <vector>
#include <map>
template <typename idxT, typename capT>
class MaximumFlow_Ford
{
private:
    idxT _size;
    std::vector<std::map<idxT, capT>> _graph;
    capT _INF;
    std::vector<std::map<idxT, capT>> _rest, _flowed;
    std::vector<idxT> _visited;
    
    idxT _goal, _cnt;
    capT _flow_total;
    capT min(const capT& a, const capT& b)
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
            if(_visited[next] < _cnt && cap > 0)
            {
                capT f = dfs(next, min(flow, cap));
                if(f > 0)
                {
                    cap -= f;
                    _flowed[next][now] += f;
                    return f;
                }
            }
        }
        for(auto& [next, cap] : _flowed[now])
        {
            if(_visited[next] < _cnt && cap > 0)
            {
                capT f = dfs(next, min(flow, cap));
                if(f > 0)
                {
                    cap -= f;
                    _flowed[next][now] += f;
                    return f;
                }
            }
        }
        return 0;
    }
    
public:
    explicit MaximumFlow_Ford(void) {}
    explicit MaximumFlow_Ford(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF) {init(size, graph, INF);}
    void init(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF)
    {
        _size = size;
        _graph = graph;
        _INF = INF;
    }
    void solve(idxT start, idxT goal)
    {
        _rest = _graph;
        _flowed.assign(_size, std::map<idxT, capT>{});
        for(idxT i = 0; i < _size; ++i)
        {
            for(auto& [j, cap] : _graph[i])
            {
                _flowed[j][i] = 0;
            }
        }
        
        _flow_total = 0;
        _goal = goal;
        _visited.assign(_size, -1);
        for(_cnt = 0;; ++_cnt)
        {
            capT flow = dfs(start, _INF);
            if(flow == 0)
                break;
            _flow_total += flow;
        }
    }
    capT flow_total(void) {return _flow_total;}
    capT flow_vertex(idxT idx)
    {
        if(idx == _goal)
            return _flow_total;
        capT flow = 0;
        for(auto& [to, cap] : _graph[idx])
        {
            flow += _flowed[to][idx];
        }
        return flow;
    }
    capT flow_edge(idxT from, idxT to)
    {
        if(_graph[from].find(to) == _graph[from].end())
            return -1;
        return _flowed[to][from];
    }
};

/* ※機能はDinic法と同じ
template <typename idxT, typename capT>
class MaximumFlow_Ford
{
    //宣言 後にinit()で初期化
    explicit MaximumFlow_Ford(void);
    //頂点数、最大流量を重みにもつ有向グラフ、無限大(十分大きい値)を指定して初期化
    explicit MaximumFlow_Ford(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF);
    void init(idxT size, const std::vector<std::map<idxT, capT>>& graph, capT INF);
    
    //頂点startから頂点goalに向けてフローを流したときの最大流量を求める
    void solve(idxT start, idxT goal);
    
    //!以下の関数はsolve()実行後に使用
    //頂点goalに流れ込む最大流量を返す
    capT flow_total(void);
    //頂点goalに流れこむ流量が最大になるときの、頂点idxを流れる流量を返す
    capT flow_vertex(idxT idx);
    //頂点goalに流れこむ流量が最大になるときの、頂点from-to間の辺を流れる流量を返す 辺が存在しない場合は-1を返す
    capT flow_edge(idxT from, idxT to);
};
*/
