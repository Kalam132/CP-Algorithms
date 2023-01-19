#include<bits/stdc++.h>
using namespace std;
const int LG = 21, N = 1 << LG, Mod = 998244353;
int rev[N + 5];
inline int Power(int a, int b)
{
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % Mod)
        if (b & 1) ret = 1ll * ret * a % Mod;
    return (ret);
}
inline void NTT(int * F, int n, bool inv)
{
    int d = LG - __builtin_ctz(n);
    for (int i = 0; i < n; i++)
        if (i < (rev[i] >> d))
            swap(F[i], F[(rev[i] >> d)]);
    for (int len = 1; len < n; len <<= 1)
    {
        int wn = Power(3, (Mod - 1) / (len << 1));
        if (inv) wn = Power(wn, Mod - 2);
        for (int i = 0; i < n; i += (len << 1))
            for (int j = i, w = 1; j < i + len; j++)
            {
                int a = 1ll * F[j + len] * w % Mod;
                F[j + len] = F[j] - a; F[j] += a;
                if (F[j + len] < 0)
                    F[j + len] += Mod;
                if (F[j] >= Mod)
                    F[j] -= Mod;
                w = 1ll * w * wn % Mod;
            }
    }
    if (inv)
        for (int i = 0, rn = Power(n, Mod - 2); i < n; i++)
            F[i] = 1ll * F[i] * rn % Mod;
}
int n, k, dp[N];
int main()
{
    for (int i = 0; i < N; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (LG - 1));
    scanf("%d%d", &n, &k);
    for (int i = 0, d; i < k; i++)
        scanf("%d", &d), dp[d] = 1;
    NTT(dp, N, 0);
    for (int i = 0; i < N; i++)
        dp[i] = Power(dp[i], n >> 1);
    NTT(dp, N, 1);
    int tot = 0;
    for (int i = 0; i < N; i++)
        tot = (tot + 1ll * dp[i] * dp[i]) % Mod;
    return !printf("%d", tot);
}
