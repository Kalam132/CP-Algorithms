// KALAM
# include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 77;
// WARNING : structure changed
struct DSU {
    vector < int > p;
    int n;
    DSU(int _n) {
        n = _n;
        reset();
    }
    void reset() {
        p.resize(n + 1);
        fill(p.begin(), p.end(), -1);
    }
    int get(int x) {
        return p[x] <= 0 ? x : (p[x] = get(p[x]));
    }
    inline bool unite(int v, int u) {
        v = get(v);
        u = get(u);
        if (v == u) return 0;
        if (p[v] < p[u]) swap(v, u);
        p[u] += p[v];
        p[v] = u;
        return 1;
    }
};
int main() {

    return 0;
}
