#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 10000;
int cnt[26][MAXN+1];
int nxt[MAXN][26];
int shuffcnt[26];
int Acnt[26];
int totals[26];
int main() {
    string S;
    cin >> S;
    int n = S.size();
    assert(n%2 == 0);
    reverse(S.begin(), S.end());
    for (int i=0; i<n; ++i) {
        for (int j=0; j<26; ++j) {
            cnt[j][i+1] = cnt[j][i];
        }
        ++cnt[S[i]-'a'][i+1];
    }
    for (int j=0; j<26; ++j) {
        nxt[n-1][j] = -1;
    }
    nxt[n-1][S[n-1]-'a'] = n-1;
    for (int i=n-2; i>=0; --i) {
        for (int j=0; j<26; ++j) {
            nxt[i][j] = nxt[i+1][j];
        }
        nxt[i][S[i]-'a'] = i;
    }

    for (int c=0; c<26; ++c) {
        assert(cnt[c][n]%2 == 0);
        totals[c] = cnt[c][n]/2;
    }

    string sol;
    int start = 0;
    while ((int)sol.size() < n/2) {
        assert(start < n);
        for (int c=0; c<26; ++c) {
            if (Acnt[c] == totals[c]) continue;
            int p = nxt[start][c];
            if (p == -1) continue;
            bool ok = true;
            for (int j=0; j<26; ++j) {
                if (shuffcnt[j]+(cnt[j][p]-cnt[j][start]) > totals[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                sol += char(c + 'a');
                for (int j=0; j<26; ++j) {
                    shuffcnt[j] += cnt[j][p] - cnt[j][start];   
                }
                ++Acnt[c];
                start = p + 1;
                break;
            }
        }
    }
    assert(int(sol.size()) == n/2);
    cout << sol << '\n';
    vector<int> tst(26);
    for (int i=0; i<(int)sol.size(); ++i) {
        ++tst[sol[i]-'a'];
    }
    for (int j=0; j<26; ++j) {
        assert(tst[j] == totals[j]);
    }
    return 0;
}
                    
 