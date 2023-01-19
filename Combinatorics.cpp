// KALAM
# include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 77 , MD = 1000000007;

struct Combinatorics {
    int n , MOD;
    vector < int > fact , invfact;
    Combinatorics(int _n , int _MOD) {
        MOD = _MOD;
        n = _n;
        fact.resize(n + 1);
        invfact.resize(n + 1);
        fact[0] = invfact[0] = 1;
        for(int i = 1;i <= n;++ i)
            fact[i] = (fact[i - 1] * 1ll * i) % MOD;
        invfact[n] = power(fact[n] , MOD - 2);
        for(int i = n - 1;i > 0;-- i)
            invfact[i] = (invfact[i + 1] * 1ll * (i + 1)) % MOD;
    }
    int power(int x , long long y) {
        int r = 1;
        for(;y;y >>= 1 , x = x * 1ll * x % MOD)
            if(y & 1)
                r = r * 1ll * x % MOD;
        return r;
    }
    inline int combine(int x , int y){
        if(x > y || x < 0)
            return 0;
        return fact[y] * 1ll * invfact[x] % MOD * 1ll * invfact[y - x] % MOD;
    }
};

Combinatorics C(100 , MD);
int main() {


	return 0;
}
