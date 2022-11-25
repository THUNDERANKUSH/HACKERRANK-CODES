#include <bits/stdc++.h>
using namespace std;
#define fo(i,n) for(int i=0;i<(n);i++)
#define MOD 1000000007
#define PB push_back
typedef long long ll;

int N, M;
vector<int> p, m;
ll ans;

int main () {
        scanf("%d %d", &N, &M);
        fo(i, N) {
                int a, b; scanf("%d %d", &a, &b);
                p.PB(a), m.PB(b+1);
        }
        sort(p.begin(), p.end()), sort(m.begin(), m.end());
        fo(i, M) {
                int a, b; scanf("%d %d", &a, &b);
                ans += N
                        - int(upper_bound(m.begin(), m.end(), a) - m.begin())
                        - int(p.end() - upper_bound(p.begin(), p.end(), b));
        }
        printf("%lld\n", ans);
        return 0;
}