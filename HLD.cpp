# include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 77;
// changed to vector style
struct Tree {
    int n, tim = 1;
    vector < int > d, up, par, sz, st, en, who;
    vector < vector < int > > adj;
    Tree(int _n) {
        n = _n;
        d.resize(n + 1);
        up.resize(n + 1);
        par.resize(n + 1);
        sz.resize(n + 1);
        st.resize(n + 1);
        en.resize(n + 1);
        who.resize(n + 1);
        adj.resize(n + 1);
    }
    void add_edge(int v, int u) {
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    void dfs_sz(int v) {
        sz[v] = 1;
        for (int u: adj[v]) {
            if (find(adj[u].begin(), adj[u].end(), v) != adj[u].end())
                adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
            d[u] = d[v] + 1;
            par[u] = v;
            dfs_sz(u);
            sz[v] += sz[u];
        }
    }
    void dfs_hv(int v) {
        who[tim] = v;
        st[v] = tim++;
        sort(adj[v].begin(), adj[v].end(), [ & ](int x, int y) {
            return sz[x] > sz[y];
        });
        int cnt = 0;
        for (int u: adj[v]) {
            up[u] = u;
            if (cnt++ == 0)
                up[u] = up[v];
            dfs_hv(u);
        }
        en[v] = tim;
    }
    inline int get_lca(int v, int u) {
        while (up[v] != up[u]) {
            if (d[up[v]] < d[up[u]])
                swap(v, u);
            v = par[up[v]];
        }
        if (d[v] > d[u])
            swap(v, u);
        return v;
    }
    inline int get_par(int v, int k) {
        while (d[v] - d[up[v]] < k)
            k -= d[v] - d[up[v]] + 1, v = par[up[v]];
        return who[st[v] - k];
    }
    inline int get_kth(int v, int u, int k) {
        int lca = get_lca(v, u);
        if (k <= d[v] - d[lca] + 1)
            return get_par(v, k - 1);
        k -= d[v] - d[lca] + 1;
        return get_par(u, d[u] - d[lca] - k);
    }
    inline int get_distance(int v, int u) {
        return d[v] + d[u] - (d[get_lca(v, u)] << 1);
    }
    void build_hld(int root) {
        for (int i = 0; i <= n; ++i)
            d[i] = st[i] = en[i] = sz[i] = par[i] = up[i] = who[i] = 0;
        tim = 1;
        up[root] = root;
        dfs_sz(root);
        dfs_hv(root);
    }
};

int main() {

    return 0;
}
