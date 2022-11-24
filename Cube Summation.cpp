#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 110;

int T, N, M, X1, Y1, Z1, X2, Y2, Z2, Val[NMAX][NMAX][NMAX];
long long Aib[NMAX][NMAX][NMAX];
char Type[20];

int LSB(int X)
{
    return (X & (X - 1)) ^ X;
}

void Update(int X, int Y, int Z, int Val)
{
    for(int i = Y; i <= N; i += LSB(i))
        for(int j = Z; j <= N; j += LSB(j))
            Aib[X][i][j] += Val;
}

long long Query(int X, int Y, int Z)
{
    long long Now = 0;
    for(int i = Y; i; i -= LSB(i))
        for(int j = Z; j; j -= LSB(j))
            Now += Aib[X][i][j];
    return Now;
}

long long Sum(int X1, int Y1, int Z1, int X2, int Y2, int Z2)
{
    long long Ans = 0;
    for(int i = X1; i <= X2; ++ i)
        Ans += (Query(i, Y2, Z2) - Query(i, Y1 - 1, Z2) - Query(i, Y2, Z1 - 1) + Query(i, Y1 - 1, Z1 - 1));
    return Ans;
}

int main()
{
    cin >> T;

    for(; T; T --)
    {
        for(int i = 1; i <= N; ++ i)
            for(int j = 1; j <= N; ++ j)
                for(int k = 1; k <= N; ++ k)
                    Aib[i][j][k] = Val[i][j][k] = 0;

        cin >> N >> M;
        for(int i = 1; i <= M; ++ i)
        {
            cin >> Type;
            if(Type[0] == 'U')
            {
                int W;
                cin >> X1 >> Y1 >> Z1 >> W;
                Update(X1, Y1, Z1, -Val[X1][Y1][Z1]);
                Update(X1, Y1, Z1, W);
                Val[X1][Y1][Z1] = W;
            }else
            {
                cin >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2;
                cout << Sum(X1, Y1, Z1, X2, Y2, Z2) << "\n";
            }
        }
    }
}