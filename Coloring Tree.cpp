#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

#define foreach(e, x) for(__typeof(x.begin()) e = x.begin(); e != x.end(); ++ e)
#define next nxt

const int N = 100000 + 10;
const int MOD = 1000000000 + 7;

int n, m, r;
int tot;
vector<int> adj[N];
int color[N];
int father[N];
int sqn[N];
int ret[N];
int ord[N][2];
int next[N];
int c[N];
pair< pair<int, int>, int> query[N];

void dfs(int u)
{
	sqn[tot] = color[u];
	ord[u][0] = tot ++;
	foreach(it, adj[u]) {
		int v = *it;
		if (v == father[u]) continue;
		father[v] = u;
		dfs(v);
	}
	ord[u][1] = tot;
}

void add(int u, int x)
{
	for( ; u <= n; u += u & -u)
		c[u] += x;
}

int ask(int u)
{
	int ret = 0;
	for( ; u; u -= u & -u)
		ret += c[u];
	return ret;
}

void solve()
{
	cin >> n >> m >> r;
	int u, v;
	for(int i = 1; i < n; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	-- r;
	father[r] = -1;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", &color[i]);
	}
	tot = 0;
	dfs(r);
	for(int i = 0; i < n; ++ i) {
		query[i] = make_pair(make_pair(ord[i][0], ord[i][1]), i);
	}
	sort(query, query + n);
	map<int, int> s;
	for(int i = n - 1; i >= 0; -- i) {
		if (s.count(sqn[i]) == 0) {
			next[i] = -1;
		} else {
			next[i] = s[sqn[i]];
		}
		s[sqn[i]] = i;
	}
	foreach(it, s) {
		add(it->second + 1, 1);
	}
	int l, r;
	int ptr = 0;
	for(int i = 0; i < n; ++ i) {
		l = query[i].first.first;
		r = query[i].first.second;
		for ( ; ptr < l; ) {
			if (next[ptr] != -1)
				add(next[ptr] + 1, 1);
			++ ptr;
		}
		ret[query[i].second] = ask(r) - ask(l);
	}
	for(int i = 0; i < n; ++ i) {
	}
	for(int i = 0; i < m; ++ i) {
		scanf("%d", &u);
		-- u;
		printf("%d\n", ret[u]);
	}
}

int main()
{
	solve();
	return 0;
}
