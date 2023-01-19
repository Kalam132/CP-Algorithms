// KALAM
# include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 77 , L = 26;
// WARNING : changed structure
struct Fenwick {
    vector < int > f;
    int n;
    Fenwick(int _n) {
        n = _n;
        f.resize(n + 1);
    }
    void add(int x , int val) {
        assert(x > 0);
        for(;x <= n;x += x & - x)
            f[x] += val;
    }
    int get(int x) {
        if(x <= 0) return 0;
        int r = 0;
        for(;x;x -= x & - x)
            r += f[x];
        return r;
    }
    int get(int l , int r) {
        return get(r) - get(l - 1);
    }
};

int main() {

    return 0;
}
