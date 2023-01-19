# include<bits/stdc++.h>

using namespace std;

struct TWOSAT {
	int n;
	vector < vector < int > > adj;
	vector < int > res;
	vector < int > mark;
	vector < int > topological;
	TWOSAT(int _n) {
		n = _n;
		adj.resize(2 * n + 2);
		res.resize(n + 1);
		mark.resize(2 * n + 2);
	}
	void add_condition(int x , int y) {
		adj[1 ^ x].push_back(y);
		adj[1 ^ y].push_back(x);
	}
	void dfs(int v) {
		mark[v] = 1;
		for(int u : adj[v])
			if(! mark[u])
				dfs(u);
		topological.push_back(v);
	}
	bool solve() {
		fill(mark.begin() , mark.end() , 0);
		for(int i = 2;i <= 2 * n + 1;++ i)
			if(! mark[i])
                    dfs(i);
		fill(mark.begin() , mark.end() , 0);
		for(int x : topological)
			if(! mark[x >> 1])
				mark[x >> 1] = 1 , res[x >> 1] = (1 ^ (x & 1));
		for(int v = 2;v <= 2 * n + 1;++ v)
			for(int u : adj[v])
				if(res[v >> 1] == (1 ^ (v & 1)) && res[u >> 1] != (1 ^ (u & 1)))
					return false;
		return true;
	}
};

int main() {

	return 0;
}
