# include<bits/stdc++.h>

using namespace std;

const int N = 1000 + 77;
// tested once
struct Dinic {
    struct Edge {
        int v , u;
        long long cap , flow;
        Edge(int _v , int _u , long long _cap) {
            v = _v;
            u = _u;
            cap = _cap;
            flow = 0;
        }
        long long get_cap(int _v) {
            return (v == _v ? cap - flow : flow);
        }
        int get_end(int st) {
            return st ^ v ^ u;
        }
        void change(int _v , long long amount) {
            flow += (v == _v ? amount : -amount);
        }
    };
    const long long FLOW_MAX = 2e18;
    int n , source , sink;
    vector < vector < Edge* > > adj;
    vector < int > dist;
    vector < int > edge_ptr;
    queue < int > que;
    Dinic(int _n) {
        n = _n;
        adj.resize(n + 1);
        dist.resize(n + 1);
        edge_ptr.resize(n + 1);
    }
    void add_edge(int v , int u , long long cap) {
        Edge* edge = new Edge(v , u , cap);
        adj[v].push_back(edge);
        adj[u].push_back(edge);
    }
    void bfs(int st) {
        fill(dist.begin() , dist.end() , n + 1);
        dist[st] = 0;
        que.push(st);
        while(! que.empty()) {
            int v = que.front();
            que.pop();
            for(Edge* edge : adj[v]) {
                int u = edge->get_end(v);
                if(dist[u] <= dist[v] + 1) continue ;
                if(edge->get_cap(v) > 0) {
                    dist[u] = dist[v] + 1;
                    que.push(u);
                }
            }
        }
    }
    long long dfs(int v , long long pushed) {
        if(pushed == 0) return 0;
        if(v == sink) return pushed;
        while(edge_ptr[v] < adj[v].size()) {
            Edge* edge = adj[v][edge_ptr[v]];
            int u = edge->get_end(v);
            long long w = edge->get_cap(v);
            if(dist[u] != dist[v] + 1) {
                ++ edge_ptr[v];
                continue ;
            }
            long long aft = dfs(u , min(w , pushed));
            if(aft == 0) {
                ++ edge_ptr[v];
                continue ;
            }
            edge->change(v , aft);
            return aft;
        }
        return 0;
    }
    long long calculate(int _st , int _en) {
        source = _st;sink = _en;
        long long flow = 0;
        while(true) {
            bfs(source);
            if(dist[sink] >= n)
                break ;
            fill(edge_ptr.begin() , edge_ptr.end() , 0);
            while(true) {
                long long pushed = dfs(source , FLOW_MAX);
                if(pushed == 0) break ;
                flow += pushed;
            }
        }
        return flow;
    }
};


int main() {

    Dinic d(3);
    d.add_edge(1,2 , 1);
    d.add_edge(2, 3,2);
    cout << d.calculate(1, 3);
    return 0;
}
