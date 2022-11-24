#include <bits/stdc++.h>
using namespace std;
#define fo(i,a,b) for(int i=(a);i<(b);i++)
#define MOD 1000000007
#define MT make_tuple
#define PB push_back
typedef long long ll;

int tst;
ll T, A, N, D, mx;

ll g (ll i, ll j) {
    return j*(j+1)/2 - i*(i-1)/2;
}

int main () {
    cin >> tst;
    while (tst--) {
        mx = -1;
        cin >> T >> A >> N >> D;
        if (D == 1) {
            cout << T*A << '\n';
            continue;
        }
        for (ll l = 0; l <= T; l++) {
            ll sum = 0;
            ll x = T-N+1, y = N-1;
            ll ls = A-(D-1), rs = D-1;
            if (ls * l < x) continue;
            if (rs * l > y) continue;

            ll lw = x / l; //this is how many full ones on left
            ll lrem = x - lw * l; //this is how many remain
            //from A-D+1-lw+1 to A-D+1, times l
            sum += g(A-D+1-lw+1, A-D+1) * l + lrem * (A-D+1-lw);
            sum += g(A-D+2, A-1) * l + (y - l * (D-2)) * A;
            mx = max(mx, sum);
        }
        if (mx == -1) cout << "SAD" << '\n';
        else cout << mx << '\n';
    }
    return 0;
}