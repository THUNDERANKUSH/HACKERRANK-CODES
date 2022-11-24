import math

t = int(input())
for i in range(t):
    ans=1
    sumb=0
    n = int(input())
    str1 = input()
    for b in str1.split():
        b=int(b)
        sumb+=b
        ans*=b**(b-1)
        ans = ans % 1000000007


    ans*=sumb**(n-2)
    ans = ans % 1000000007
    print( int(ans))
