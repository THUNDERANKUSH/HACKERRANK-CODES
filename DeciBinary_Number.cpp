#include <bits/stdc++.h>
using namespace std;
#define fora(i, l, r) for (int i = (int)l; i < (int)r; ++i)
#define ford(i, r, l) for (int i = (int)r; i >= (int)l; --i)
constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 2e5 + 1;
using ll = long long;
ll N, M, K;
const ll MAXD = 22, MAXS = 300003;
ll dp[MAXD][MAXS];
ll nm[MAXS];
ll F(ll d, ll s) {
if (d == -1 && s == 0)
return 1;
if (d == -1)
return 0;
if (dp[d][s] != -1)
return dp[d][s];
dp[d][s] = 0;
fora (i, 0, 10) {
if ((1LL << d) * i > s)
break;
dp[d][s] += F(d - 1, s - (1LL << d) * i);
}
return dp[d][s];
}
void Init() {
memset(dp, -1, sizeof(dp));
fora (i, 0, MAXS) {
nm[i] = F(MAXD-1, i);

}
fora (i, 1, MAXS) {
nm[i] += nm[i-1];
}
}
void Solution() {
Init();
while (N--) {
cin >> K;
if (K == 1) cout << "0\n";
else {
auto s = lower_bound(nm, nm + MAXS, K) - nm;
ll g = K - nm[s-1];
int d = 0;
for (int i = -1; F(i, s) < g; ++i)
d = i + 1;
while (d >= 0) {
ll val = 0;
fora (i, 0, 10) {
if ((s - (1LL << d) * i) >= 0) {
val += F(d-1, s-(1LL << d) * i);
}
if (val >= g) {
cout << i;
g -= val - F(d-1, s-(1LL<<d)*i);
s -= (1LL << d) * i;
break;
}
}
--d;
}
cout << '\n';
}
}
}
int main() {
#ifdef MY_DEBUG
freopen("in.txt", "r", stdin);
#endif
ios::sync_with_stdio(false);
cin.tie(nullptr), cout.tie(nullptr);
while (cin >> N) {
Solution();
}
return 0;
}