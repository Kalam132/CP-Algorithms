// KALAM
# include<bits/stdc++.h>

using namespace std;

const int N = 200000 + 77;
string s;
int n , f[N];
int main(){
	cin >> s;
	int n = s.size();
	f[0] = - 1;
	for(int i = 1;i <= n;i ++){
		int cur = f[i - 1];
		while(cur > - 1 && s[i - 1] != s[cur]){
			cur = f[cur];
		}
		f[i] = cur + 1;
		cout << f[i] << ' ';
	}
	return 0;
}

