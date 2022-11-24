#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define forit(s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it ++)
#define N 1000100
#define all(a) a.begin(), a.end()
#define ll long long
#define pii pair <int, int>
#define sz(a) (int)a.size()
#define vi vector <int>
#define forn(i, n) for(int i = 0; i < n; i ++)

const int inf = (int)(1e9);
const int mod = inf + 7;
const double pi = acos(-1.0);
const double eps = 1e-9;

int n, a[N];

int main () {

    #ifdef LOCAL
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif

    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    vector <int> d(N, 0);

    d[0] = -inf;
    for(int i = 1; i < N; i++) d[i] = inf;

    for(int i = 0; i < n; i++) {
        int j = upper_bound(all(d), a[i]) - d.begin();
        if(d[j - 1] < a[i] && a[i] < d[j]) d[j] = a[i];
    }

    for(int i = N - 1;; i--) {
        if(d[i] != inf) {
            cout << i;
            return 0;
        }
    }

    return 0;
}
