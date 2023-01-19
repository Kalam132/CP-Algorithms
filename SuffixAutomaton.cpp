// KALAM
# include<bits/stdc++.h>

using namespace std;

const int N = 1000 + 77;

struct SuffixAutomaton {
   int last , n , sz;
   int link[N << 1];
   int len[N << 1];
   char S[N];
   map < char , int > adj[N << 1];
   inline void __init() {
      last = sz = 1;
      link[1] = len[1] = 0;
   }
   inline void Clear() {
      last = n = sz = 0;
      memset(link , 0 , sizeof link);
      memset(len , 0 , sizeof len);
      memset(S , 0 , sizeof S);
      for(int i = 0;i < (N << 1);++ i)
         adj[i].clear();
      __init();
   }
   inline void Add(char c) {
      S[++ n] = c;
      int p = last;
      len[++ sz] = len[last] + 1;
      last = sz;
      while(p > 0 && adj[p][c] == 0)
         adj[p][c] = last , p = link[p];
      if(p == 0) {
         link[last] = 1;
         return ;
      }
      int q = adj[p][c];
      if(len[p] + 1 == len[q]) {
         link[last] = q;
         return ;
      }
      int qi = ++ sz;
      len[qi] = len[p] + 1;
      adj[qi] = adj[q];
      link[qi] = link[q];
      link[last] = link[q] = qi;
      while(p > 0 && adj[p][c] == q)
         adj[p][c] = qi , p = link[p];
   }
   inline void Print(int v) {
      cerr << v << " : " << endl;
      cerr << "link = " << link[v] << endl;
      for(auto x : adj[v])
         cerr << x.first << ' ' << x.second << endl;
      cerr << endl << endl;
   }
   inline void PrintAll() {
      for(int i = 1;i <= sz;++ i)
         Print(i);
   }
};

int main() {

   return 0;
}
