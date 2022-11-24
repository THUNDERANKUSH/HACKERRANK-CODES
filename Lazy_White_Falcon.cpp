
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
const int LG_N = 20;

vector<int> adj[N];
int n, q;

int tree[2*N];
vector<int> euler;
int first[N], last[N];

int H[N], P[N][LG_N];
int val[N];

void dfs(int u, int p, int h) {
    H[u] = h;
    P[u][0] = p;
    for(int i = 1;i < LG_N;i++) {
        P[u][i] = P[P[u][i-1]][i-1];
    }
    first[u] = euler.size();
    euler.push_back(u);
    for(int v : adj[u]) {
        if(v == p) {
            continue;
        }
        dfs(v, u, h+1);
    }
    last[u] = euler.size();
    euler.push_back(u);
}
int lca(int u, int v) {
    if(H[u] < H[v]) swap(u, v);
    for(int i = LG_N-1;i >= 0;i--) {
        if(H[P[u][i]] >= H[v]) {
            u = P[u][i];
        }    
    }
    if(u == v) {
        return u;
    }
    for(int i = LG_N-1;i >= 0;i--) {
        if(P[u][i] != P[v][i]) {
            u = P[u][i];
            v = P[v][i];
        }
    }
    return P[u][0];
}
void update(int idx, int val) {
    while(idx < euler.size()) {
        tree[idx] += val;
        idx += idx & (-idx);
    }
}
int query(int idx) {
    int ans = 0;
    while(idx > 0) {
        ans += tree[idx];
        idx -= idx & (-idx);
    }
    return ans;
}
int main() {

    ios::sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    euler.resize(1, 0);
    dfs(0, 0, 0);
   
    for(int i = 0;i < q;i++) {
        int type;
        cin >> type;
        if(type == 1) {
            int u, x;
            cin >> u >> x;
            update(first[u], x - val[u]);
            update(last[u],  val[u] - x);
            val[u] = x;
        }else {
            int u, v;
            cin >> u >> v;
            int l = lca(u, v);
            int ans = query(first[u]) + query(first[v]);
            ans = ans - 2 * query(first[l]) + val[l];
            cout << ans << "\n";
        }
    }
    return 0;
}
