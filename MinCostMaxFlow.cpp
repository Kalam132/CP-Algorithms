# include<bits/stdc++.h>

using namespace std;
// tested once
struct MinCostMaxFlow {
    struct Edge {
        int v , u;
        long long cost , cap , flow;
        Edge(int _v , int _u , long long _cost , long long _cap) {
            v = _v;
            u = _u;
            cap = _cap;
            cost = _cost;
            flow = 0;
        }
        long long get_cap(int _v) {
            return (v == _v ? cap - flow : flow);
        }
        long long get_cost(int _v) {
            return (v == _v ? cost : -cost);
        }
        int get_end(int st) {
            return st ^ v ^ u;
        }
        void change(int _v , long long amount) {
            flow += (v == _v ? amount : -amount);
        }
    };
    const long long FLOW_MAX = 2e18;
    const long long COST_MAX = 2e18;
    int n , source , sink;
    vector < vector < Edge* > > adj;
    vector < long long > dist;
    vector < Edge* > dist_par;
    vector < bool > in_queue;
    queue < int > que;

    MinCostMaxFlow(int _n) {
        n = _n;
        adj.resize(n + 1);
        dist.resize(n + 1);
        dist_par.resize(n + 1);
        in_queue.resize(n + 1);
    }
    void add_edge(int v , int u , long long cost , long long cap) {
        Edge* edge = new Edge(v , u , cost , cap);
        adj[v].push_back(edge);
        adj[u].push_back(edge);
    }
    void spfa() {
        fill(dist.begin() , dist.end() , COST_MAX);
        fill(in_queue.begin() , in_queue.end() , false);
        fill(dist_par.begin() , dist_par.end() , nullptr);
        dist[source] = 0;
        que.push(source);
        while(! que.empty()) {
            int v = que.front();
            que.pop();
            in_queue[v] = false;
            for(Edge* edge : adj[v]) {
                int u = edge->get_end(v);
                long long cap = edge->get_cap(v);
                if(cap == 0) continue ;
                long long cost = edge->get_cost(v);
                if(dist[u] > dist[v] + cost) {
                    dist[u] = dist[v] + cost;
                    dist_par[u] = edge;
                    if(! in_queue[u]) {
                        in_queue[u] = true;
                        que.push(u);
                    }
                }
            }
        }
    }

    pair < long long , long long > calculate(int _source , int _sink) {
        source = _source;
        sink = _sink;
        long long flow = 0;
        long long cost = 0;
        while(true) {
            spfa();
            if(dist_par[sink] == nullptr) break ;
            int nw = sink;
            long long available = FLOW_MAX;
            while(nw != source) {
                int v = dist_par[nw]->get_end(nw);
                available = min(available , dist_par[nw]->get_cap(v));
                nw = v;
            }
            nw = sink;
            while(nw != source) {
                int v = dist_par[nw]->get_end(nw);
                cost -= dist_par[nw]->cost * dist_par[nw]->flow;
                dist_par[nw]->change(v , available);
                cost += dist_par[nw]->cost * dist_par[nw]->flow;
                nw = v;
            }
            flow += available;
        }
        return make_pair(flow , cost);
    }
};

int main() {

    return 0;
}

