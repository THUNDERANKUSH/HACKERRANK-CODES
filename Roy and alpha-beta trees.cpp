#include <vector> // headers {{{
#include <list>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>
#include <cstring>

#define DEBUG(x) cout << #x << ": " << x << "\n"
using namespace std; // }}}

const int Z = 1000000009;
typedef long long lint;
unordered_map<int, pair<int, int> > MEMO;
vector<lint> C;

pair<int, int> doit(const vector<int>& A, int l, int r)
{
    pair<int, int> res;
    if (l == r)
        return res;

    int p = l * 1000 + r;
    if (MEMO.count(p))
        return MEMO[p];

    for (int i = l; i < r; ++i) {
        res.first = (res.first + ((A[i] * C[i - l]) % Z) * C[r - 1 - i]) % Z;

        pair<int, int> left = doit(A, l, i);
        res.second = (res.second + left.first * C[r - 1 - i]) % Z;
        res.first = (res.first + left.second * C[r - 1 - i]) % Z;

        pair<int, int> right = doit(A, i + 1, r);
        res.second = (res.second + right.first * C[i - l]) % Z;
        res.first = (res.first + right.second * C[i - l]) % Z;
    }

    return MEMO[p] = res;
}

int main()
{
    //time_t start, end;
    //time(&start);

    //ifstream cin("test.in");
    //ofstream cout("test.out");
    //fcout.precision(6);
    //fcout.setf(ios::fixed,ios::floatfield);
    ios::sync_with_stdio(false);
    const int M = 151;
    C.resize(M);
    C[0] = C[1] = 1;
    for (int i = 2; i < M; ++i) {
        lint& cur = C[i];
        for (int j = 0; j < i; ++j) {
            cur = (cur + C[j] * C[i - 1 - j]) % Z;
        }
    }

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int N;
        cin >> N;
        lint a, b;
        cin >> a >> b;
        vector<int> A(N);
        for (int j = 0; j < N; ++j) {
            cin >> A[j];
        }
        MEMO.clear();
        sort(A.begin(), A.end());
        pair<int, int> p = doit(A, 0, N);
        lint res = p.first * a - p.second * b;
        cout << (res % Z + Z) % Z << endl;
    }

    //time(&end);
    //cout << difftime(end, start) << endl;

    return 0;
}
