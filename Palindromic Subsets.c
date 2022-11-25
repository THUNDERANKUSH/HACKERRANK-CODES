

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define M 1000000007

char s[100006];
int ret[32];
int d[1<<18][32];
int f[100006];

void init(int t,int l,int r) {
    int i;
    if (r-l==1) {
        d[t][s[l]-'a']++;
        return ;
    }
    init(t<<1,l,(l+r)/2);
    init(t<<1|1,(l+r)/2,r);
    for(i=0;i<26;i++) d[t][i]=d[t<<1][i]+d[t<<1|1][i];
}

void shift(int a[],int t) {
    int b[32],i;
    for(i=0;i<26;i++) b[(i+t)%26]=a[i];
    for(i=0;i<26;i++) a[i]=b[i];
}

void update(int t,int l,int r,int a,int b,int val) {
    if (l==a && r==b) {
        d[t][26]=(d[t][26]+val)%26;
        return ;
    }
    shift(d[t],d[t][26]);
    d[t<<1][26]+=d[t][26];
    d[t<<1|1][26]+=d[t][26];
    d[t][26]=0;
    if (b<=(l+r)/2) {
        update(t<<1,l,(l+r)/2,a,b,val);
    } else if (a>=(l+r)/2) {
        update(t<<1|1,(l+r)/2,r,a,b,val);
    } else {
        update(t<<1,l,(l+r)/2,a,(l+r)/2,val);
        update(t<<1|1,(l+r)/2,r,(l+r)/2,b,val);
    }
    int i;
    for(i=0;i<26;i++) d[t][i]=0;
    for(i=0;i<26;i++) d[t][(i+d[t<<1][26])%26]+=d[t<<1][i];
    for(i=0;i<26;i++) d[t][(i+d[t<<1|1][26])%26]+=d[t<<1|1][i];
}

void query(int t,int l,int r,int a,int b) {
//    printf("%d %d %d %d %d %d %d\n",t,l,r,d[t][0],d[t][1],d[t][2],d[t][26]);
    if (l==a && r==b) {
        int i;
        for(i=0;i<26;i++) ret[(i+d[t][26])%26]+=d[t][i];
        return ;
    }
    shift(d[t],d[t][26]);
    d[t<<1][26]+=d[t][26];
    d[t<<1|1][26]+=d[t][26];
    d[t][26]=0;
    if (b<=(l+r)/2) {
        query(t<<1,l,(l+r)/2,a,b);
    } else if (a>=(l+r)/2) {
        query(t<<1|1,(l+r)/2,r,a,b);
    } else {
        query(t<<1,l,(l+r)/2,a,(l+r)/2);
        query(t<<1|1,(l+r)/2,r,(l+r)/2,b);
    }
}

int main(){
    int n,m,i;
    scanf("%d %d",&n,&m);
    scanf("%s",s);
    init(1,0,n);
    for(f[0]=i=1;i<=n;i++) if ((f[i]=f[i-1]+f[i-1])>=M) f[i]-=M;
    for(;m--;) {
        int op,l,r,val;
        scanf("%d %d %d",&op,&l,&r);
        if (op==1) {
            scanf("%d",&val);
            update(1,0,n,l,r+1,val);
        } else {
            int d1=1,d2=0;
            memset(ret,0,sizeof(ret));
            query(1,0,n,l,r+1);
         //   printf("%d %d %d\n",ret[0],ret[1],ret[2]);
            for(i=0;i<26;i++) {
                if (!ret[i]) continue;
                d2=(long long)(d2+d1)*f[ret[i]-1]%M;
                d1=(long long)d1*f[ret[i]-1]%M;
            }
            if ((d1+=d2-1)>=M) d1-=M;
            printf("%d\n",d1);
        }
    }
    return 0;
}