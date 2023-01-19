// KALAM
# include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 77 , Mod = 1e9 + 7;

struct Hash{
	unsigned int n , ps[N] ,  Pow[N] , Base , MOD;
	string s;
	Hash (int b , int m , string t){
		s = t;n = t.size();Base = b;MOD = m;
		s = " " + s;
		Pow[0] = 1;
		for(int i = 1;i <= n;i++){Pow[i] = (Pow[i - 1] * 1ll * Base) % MOD;}
		for(int i = 1;i <= n;i++){
			ps[i] = ((ps[i - 1] * 1ll * Base) + (s[i] - 'a' + 1)) % MOD;
		}
	}
	int get(int l , int r){// [l , r]
		int A = ps[r];

		A = (A - (ps[l - 1] * 1ll * Pow[r - l + 1] % MOD) + MOD) % MOD;
		return A;
	}
};
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);


	return 0;
}
