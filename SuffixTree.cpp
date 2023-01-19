// KALAM
# include <bits/stdc++.h>

# define debug(x) cerr << #x << " = " << x << endl

using namespace std;

const int N = 100000 + 77 , LOG = 17;

struct SuffixArray {

   /// remember that the S[i] values have to be positive or this wont work properly and you may get RE

   char S[N];
   int R[N][LOG];
   int C[N] , P[N] , V[N] , H[N] , F[N] , Wh[N];
   int n;

   inline int GetLcp(int x , int y) {
      if(x < 1 || y < 1 || x > n || y > n)
         return 0;
      int res = 0;
      for(int i = LOG - 1;i >= 0;-- i)
         if(R[x][i] == R[y][i])
            res ^= (1 << i) , x += (1 << i) , y += (1 << i);
      return res;
   }

   inline void RadixSort() {
      memset(C , 0 , sizeof C);
      int m = 0;
      for(int i = 1;i <= n;++ i)
         ++ C[V[i]] , m = max(m , V[i]);
      F[0] = 1;
      for(int i = 1;i <= m;++ i)
         C[i] += C[i - 1] , F[i] = C[i - 1] + 1;
      for(int i = 1;i <= n;++ i)
         H[F[V[P[i]]] ++] = P[i];
      for(int i = 1;i <= n;++ i)
         P[i] = H[i];
   }

   inline void BuildSA() {
      for(int i = 1;i <= n;++ i)
         R[i][0] = S[i] , P[i] = i;
      for(int lg = 1;lg < LOG;++ lg) {
         int len = (1 << (lg - 1));
         for(int i = 1;i <= n;++ i)
            V[i] = (i + len > n ? 0 : R[i + len][lg - 1]);
         RadixSort();
         for(int i = 1;i <= n;++ i)
            V[i] = R[i][lg - 1];
         RadixSort();
         R[P[1]][lg] = 1;
         for(int i = 2;i <= n;++ i) {
            int fip = (P[i - 1] + len > n ? 0 : R[P[i - 1] + len][lg - 1]);
            int fi = (P[i] + len > n ? 0 : R[P[i] + len][lg - 1]);
            R[P[i]][lg] = R[P[i - 1]][lg] + 1;
            if(V[P[i - 1]] == V[P[i]] && fip == fi)
               R[P[i]][lg] = R[P[i - 1]][lg];
         }
      }
      for(int i = 1;i <= n;++ i)
         Wh[P[i]] = i;
   }
};

struct SuffixTree {
   /// remember that the memory needed is 2n
   struct edge {
      /// v is parent S[l, r] is the string written on it
      int v , u , l , r;
      inline void Print() { cerr << v << " ---> " << u << " [" << l << " " << r << "]\n"; }
   };

   int n , cntnode = 1 , cntedge = 0;
   int dist[N] , ParE[N];
   char S[N];
   SuffixArray SA;
   edge E[N];
   vector < int > adj[N];/// index of edges
   /// edges only from parent to child
   inline void BuildST() {
      SA.n = n;
      for(int i = 1;i <= n;++ i)
         SA.S[i] = S[i];
      SA.BuildSA();
      int curnode = 1;
      for(int i = 1;i <= n;++ i) {

         int id = SA.P[i];
         int lcp = (i == 1 ? 0 : SA.GetLcp(SA.P[i - 1] , SA.P[i]));

         int prvedge = -1;
         while(dist[curnode] > lcp)
            prvedge = ParE[curnode] , curnode = E[ParE[curnode]].v;

         if(lcp > dist[curnode]) {
            assert(prvedge != -1);
            int remain = lcp - dist[curnode];

            E[++ cntedge] = E[prvedge];
            E[prvedge].u = ++ cntnode;
            ParE[cntnode] = prvedge;
            E[prvedge].l = id + dist[curnode];
            E[prvedge].r = id + dist[curnode] + remain - 1;
            dist[cntnode] = dist[curnode] + remain;
            E[cntedge].v = cntnode;
            ParE[E[cntedge].u] = cntedge;
            E[cntedge].l += remain;
            curnode = cntnode;

         }
         E[++ cntedge].v = curnode;
         E[cntedge].u = ++ cntnode;
         ParE[cntnode] = cntedge;
         E[cntedge].l = id + lcp;
         E[cntedge].r = n;
         dist[cntnode] = dist[curnode] + n - id - lcp + 1;
         curnode = cntnode;
      }
      for(int i = 1;i <= cntedge;++ i)
         adj[E[i].v].push_back(i);
   }
} ST;
int n;
char S[N];
int main() {
   scanf("%s" , S + 1);
   n = strlen(S + 1);
   ST.n = n;
   for(int i = 1;i <= n;++ i)
      ST.S[i] = S[i];
   ST.BuildST();
   return 0;
}
