// KALAM
# include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 77 , Mod = 1e9 + 7;

struct SegTree{
	int n;
	long long Sum[N << 2] , a[N] , lazy[N << 2] , Min[N << 2] , Max[N << 2];
	SegTree(int n1 , long long in[N]){
		n = n1;
		for(int i = 1;i <= n;i++){
			a[i] = in[i];
		}
		build();
	}
	void build(int l = 1 , int r = 0 , int id = 1){
		if(r == 0)r = n + 1;
		if(l + 1 == r){
			Sum[id] = a[l];
			Min[id] = a[l];
			Max[id] = a[l];
			return;
		}
		build(l , (l + r) / 2 , id * 2);
		build((l + r) / 2 , r , id * 2 + 1);
		Sum[id] = Sum[id * 2] + Sum[id * 2 + 1];
		Max[id] = max(Max[id * 2] , Max[id * 2 + 1]);
		Min[id] = min(Min[id * 2] , Min[id * 2 + 1]);
	}
	void shift(int l , int r , int id){
		Sum[id * 2] += lazy[id] * (r - l);
		Sum[id * 2 + 1] += lazy[id] * (r - l);
		Min[id * 2] += lazy[id];
		Min[id * 2 + 1] += lazy[id];
		Max[id * 2] += lazy[id];
		Max[id * 2 + 1] += lazy[id];
		lazy[id * 2] += lazy[id];
		lazy[id * 2 + 1] += lazy[id];
		lazy[id] = 0;
	}
	void update(int ql , int qr , long long x , int l = 1 , int r = 0 , int id = 1){
		if(r == 0)r = n + 1;
		if(r <= ql || qr <= l)return;
		if(ql <= l && r <= qr){
			Sum[id] += x * (r - l);
			Max[id] += x;
			Min[id] += x;
			lazy[id] += x;
			return;
		}
		shift(l , r , id);
		update(ql , qr , x , l , (l + r) / 2 , id * 2);
		update(ql , qr , x , (l + r) / 2 , r , id * 2 + 1);
		Sum[id] = Sum[id * 2] + Sum[id * 2 + 1];
		Min[id] = min(Min[id * 2] ,  Min[id * 2 + 1]);
		Max[id] = max(Max[id * 2] ,  Max[id * 2 + 1]);
	}
	long long get_min(int ql , int qr , int l = 1 , int r = 0 , int id = 1){
		if(r == 0)r = n + 1;
		if(r <= ql || qr <= l)return 5e18;
		if(ql <= l && r <= qr)return Min[id];
		shift(l , r , id);
		return min(get_min(ql , qr , l , (l + r) / 2 , id * 2) , get_min(ql , qr , (l + r) / 2 , r , id * 2 + 1));
	}
	long long get_max(int ql , int qr , int l = 1 , int r = 0 , int id = 1){
		if(r == 0)r = n + 1;
		if(r <= ql || qr <= l)return -5e18;
		if(ql <= l && r <= qr)return Max[id];
		shift(l , r , id);
		return max(get_max(ql , qr , l , (l + r) / 2 , id * 2) , get_max(ql , qr , (l + r) / 2 , r , id * 2 + 1));
	}
	long long get_sum(int ql , int qr , int l = 1 , int r = 0 , int id = 1){
		if(r == 0)r = n + 1;
		if(r <= ql || qr <= l)return 0;
		if(ql <= l && r <= qr)return Sum[id];
		shift(l , r , id);
		return get_sum(ql , qr , l , (l + r) / 2 , id * 2) + get_sum(ql , qr , (l + r) / 2 , r , id * 2 + 1);
	}
};

int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	
	return 0;
}
