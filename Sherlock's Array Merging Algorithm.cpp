#pragma comment(linker, "/STACK:1000000000")
#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <bitset>
#include <fstream>
#include <deque>
#include <stack>
#include <climits>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <unordered_map>

#define ll long long
#define ld double
#define pii pair <ll, ll>
#define mp make_pair

using namespace std;

const int maxn = 1500;
const int mod = (int)1e9 + 7;

ll dp[maxn][maxn];
int v[maxn];
int n;
int lnk[maxn];
ll fac[maxn];
ll C[maxn][maxn];

ll getCC(int a, int b) {
	if (C[a][b] != -1) {
		return C[a][b];
	}

	if (a == b || b == 0) {
		C[a][b] = 1;
	} else {
		C[a][b] = (getCC(a - 1, b) + getCC(a - 1, b - 1)) % mod;
	}

	return C[a][b];
}
ll go(int pos, int cnt) {
	if (dp[pos][cnt] != -1) {
		return dp[pos][cnt];
	}

	if (cnt == 0) {
		return dp[pos][cnt] = 0;
	}

	if (pos == n) {
		return dp[pos][cnt] = 1;
	}

	ll ans = 0;

	for (int k = min(cnt, n - pos); k >= 0; k--) {
		if (lnk[pos] >= pos + k - 1) {
		   ans += (pos == 0 ? 1 : getCC(cnt, k) * fac[k] % mod) * go(pos + k, k);
		   ans %= mod;
		}
	}

	return dp[pos][cnt] = ans;
}

int main() {
	memset(C, -1, sizeof C);
	memset(dp, -1, sizeof dp);
	fac[0] = 1;

	for (int i = 1; i < maxn; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}

	cin >> n;

	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
		//v[i] = i + 1;
	}

	for (int i = n - 1; i >= 0; i--) {
		if (i == n - 1) {
			lnk[i] = i;
		} else if (v[i] < v[i + 1]) {
			lnk[i] = lnk[i + 1];
		} else {
			lnk[i] = i;
		}
	}

	cout << go(0, n) << endl;

	return 0;
}

