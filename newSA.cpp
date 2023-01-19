
# include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 77 , LOG = 20;

struct SuffixArray {

   /// S[i] values have to be positive or this wont work properly and you may get RE

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

int n;
char S[N];
SuffixArray SA;
int main() {
   scanf("%s" , S + 1);
   n = strlen(S + 1);
   SA.n = n;
   for(int i = 1;i <= n;++ i)
      SA.S[i] = S[i];
   SA.BuildSA();

   cout << SA.GetLcp(2 , 4) << endl;



   /*
   for(int i = 1;i <= n;++ i)
      for(int j = i + 1;j <= n;++ j)
         cout << i << ' ' << j << ' ' << SA.GetLcp(i , j) << endl;
   cout << endl;
   */
   return 0;
}
