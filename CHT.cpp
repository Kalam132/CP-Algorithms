// KALAM
# include <bits/stdc++.h>

# define debug(x) cerr << #x << " = " << x << endl

using namespace std;

const int N = 4000 + 77;
const int inf = 1000000000 + 77;

struct CHT {
    vector < pair < int, int > > V;
    vector < pair < int, int > > S;
    inline int Intersect(int x, int v, int xx, int vv) {
        if (v == vv)
            return -inf;
        return (xx - x) / (v - vv);
    }
    inline void Add(int x, int v) {
        V.push_back(make_pair(v, x));
    }
    inline void BuildCHT() {
        sort(V.begin(), V.end());
        int sz = V.size();
        for (int i = sz - 1; i >= 0; --i) {
            auto c = V[i];
            while (!S.empty()) {
                auto cc = S.back();
                int pos = Intersect(c.second, c.first, V[cc.second].second, V[cc.second].first);
                if (pos >= cc.first) {
                    S.pop_back();
                    continue;
                } else {
                    S.push_back(make_pair(pos, i));
                    break;
                }
            }
            if (S.empty())
                S.push_back(make_pair(inf, i));
        }
        reverse(S.begin(), S.end());
    }
    inline long long Get(int t) {
        int id = lower_bound(S.begin(), S.end(), make_pair(t, -1)) - S.begin();
        id = S[id].second;
        return V[id].second + V[id].first * 1ll * t;
    }
};

CHT C;
int n, q;
int main() {
    C.Add(-2, 1);
    C.Add(2, 0);
    C.BuildCHT();
    return 0;
}
