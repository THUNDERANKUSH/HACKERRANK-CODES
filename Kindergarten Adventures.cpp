#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }

    int start = 0;

    vector<int> D(N+1, 0);
    for(int i = 0; i < N; i++) {
        if(A[i] <= i) {
            start++;
            D[i-A[i]]--;
            D[i]++;
        } else {
            D[i-A[i]+N]--;
            D[i]++;
        }
    }

    int best = start;
    int bi = 0;
    int cur = start;
    for(int i = 0; i < N; i++) {
        if(cur > best) {
            best = cur;
            bi = i;
        }
        cur += D[i];
    }

    cout << (bi+1) << endl;
}