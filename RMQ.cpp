// KALAM
# include<bits/stdc++.h>

using namespace std;

const int N = 1000 + 77 , LOG = 20;

template < typename T>
struct SparseTable {
   function < bool(T , T) > CMP;
   T a[N];
   T A[N][LOG];
   int Log[N];
   int n;
   inline void Build() {
      for(int i = 2;i <= n;++ i) Log[i] = Log[i >> 1] + 1;
      for(int i = 1;i <= n;++ i) A[i][0] = a[i];
      for(int j = 1;j < LOG;++ j)
         for(int i = 1;i + (1 << (j - 1)) <= n;++ i)
            A[i][j] = (CMP(A[i][j - 1] , A[i + (1 << (j - 1))][j - 1]) ? A[i][j - 1] : A[i + (1 << (j - 1))][j - 1]);
   }
   inline T Get(int l , int r) {
      int ts = (Log[r - l + 1]);
      return (CMP(A[l][ts] , A[r - (1 << ts) + 1][ts]) ? A[l][ts] : A[r - (1 << ts) + 1][ts]);
   }
};

SparseTable < int > RM;
int P[N];
int main() {
   iota(P , P + 100 , 0);
   function < bool(int , int) > CMP = [&](int x , int y) { return P[x] < P[y]; };
   RM.CMP = CMP;
   scanf("%d" , & RM.n);
   for(int i = 1;i <= RM.n;++ i)
      scanf("%d" , & RM.a[i]);
   int q;
   scanf("%d" , & q);
   RM.Build();
   while(q --) {
      int x , y;
      scanf("%d %d" , & x , & y);
      printf("%d\n" , RM.Get(x , y));
   }
   return 0;
}
