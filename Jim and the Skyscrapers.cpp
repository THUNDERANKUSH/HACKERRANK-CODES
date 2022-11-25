#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int NMAX = 300010, CMAX = 1000010;

int N, V[NMAX], Right[NMAX];
stack<int> S;
vector<int> Val[CMAX];
long long Ans;

int main()
{

    scanf("%i", &N);
    for(int i = 1; i <= N; ++ i)
    {
        scanf("%i", &V[i]);
        Val[V[i]].push_back(i);
    }

    V[N + 1] = CMAX;

    S.push(N + 1);
    for(int i = N; i; -- i)
    {
        while(!S.empty() && V[S.top()] <= V[i]) S.pop();
        Right[i] = S.top();
        S.push(i);
    }

    for(int i = CMAX - 1; i >= 1; -- i)
    {
        int Ptr = 0;
        for(int j = 0; j < Val[i].size(); )
        {
            while(Ptr < Val[i].size() && Val[i][Ptr] <= Right[ Val[i][j] ]) Ptr ++;
            int Len = Ptr - j;
            Ans += 1LL * Len * (Len - 1);
            j = Ptr;
        }
    }

    printf("%lld", Ans);
}