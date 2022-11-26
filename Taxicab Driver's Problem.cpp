#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll rl()
{
  ll x;
  scanf("%lld", &x);
  return x;
}

const int N = 100000;
pair<ll, ll> a[N], b[N];
vector<int> e[N];
bool cut[N];
int size[N], fenwick[N];
ll H, V, c[N];

int getSize(int v, int p)
{
  size[v] = 1;
  for (int u: e[v])
    if (u != p && ! cut[u])
      size[v] += getSize(u, v);
  return size[v];
}

int getDist(int v, int p, int i, ll hh, ll vv)
{
  hh += abs(a[v].fi - a[p].fi);
  vv += abs(a[v].se - a[p].se);
  b[i++] = {hh, vv};
  for (int u: e[v])
    if (u != p && ! cut[u])
      i = getDist(u, v, i, hh, vv);
  return i;
}

ll calc(int l, int r)
{
  int n = r-l;
  ll ret = 0;
  sort(b+l, b+r);
  FOR(i, l, r)
    c[i-l] = b[i].se;
  sort(c, c+n);
  fill_n(fenwick, n, 0);
  for (int j = l, i = r; --i >= l; ) {
    for (; j < r && b[j].fi+b[i].fi <= H; j++)
      for (int x = lower_bound(c, c+n, b[j].se) - c; x < n; x |= x+1)
        fenwick[x]++;
    for (int x = upper_bound(c, c+n, V-b[i].se) - c; x; x &= x-1)
      ret += fenwick[x-1];
  }
  return ret;
}

pair<int, ll> divide(int l, int v)
{
  getSize(v, -1);
  int nn = size[v], p = -1;
  for(;;) {
    int ch = -1;
    for (int u: e[v])
      if (u != p && ! cut[u] && 2*size[u] >= nn) {
        ch = u;
        break;
      }
    if (ch < 0) break;
    p = v;
    v = ch;
  }
  cut[v] = true;
  b[l] = {0, 0};
  int i = l+1;
  ll ret = 0;
  for (int u: e[v])
    if (! cut[u]) {
      auto r = divide(i, u);
      ret += r.se;
      getDist(u, v, i, 0, 0);
      ret -= calc(i, r.fi);
      i = r.fi;
    }
  cut[v] = false;
  ret += calc(l, i) - 1; // 1 for root<->root
  return {i, ret};
}

int main()
{
  int n = ri();
  H = rl();
  V = rl();
  REP(i, n) {
    a[i].fi = rl();
    a[i].se = rl();
  }
  REP(i, n-1) {
    int v = ri()-1, u = ri()-1;
    e[v].pb(u);
    e[u].pb(v);
  }
  printf("%lld\n", ll(n-1)*n-divide(0, 0).se >> 1);
}
