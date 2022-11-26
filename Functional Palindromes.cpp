#include <bits/stdc++.h>
using namespace std ;

#define ft first
#define sd second
#define pb push_back
#define all(x) x.begin(),x.end()

#define ll long long int
#define vi vector<int>
#define vii vector<pair<int,int> >
#define pii pair<int,int>
#define plii pair<pair<ll, int>, int>
#define piii pair<pii, int>
#define viii vector<pair<pii, int> >
#define vl vector<ll>
#define vll vector<pair<ll,ll> >
#define pll pair<ll,ll>
#define pli pair<ll,int>
#define mp make_pair
#define ms(x, v) memset(x, v, sizeof x)

#define sc1(x) scanf("%d",&x)
#define sc2(x,y) scanf("%d%d",&x,&y)
#define sc3(x,y,z) scanf("%d%d%d",&x,&y,&z)

#define scll1(x) scanf("%lld",&x)
#define scll2(x,y) scanf("%lld%lld",&x,&y)
#define scll3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)

#define pr1(x) printf("%d\n",x)
#define pr2(x,y) printf("%d %d\n",x,y)
#define pr3(x,y,z) printf("%d %d %d\n",x,y,z)

#define prll1(x) printf("%lld\n",x)
#define prll2(x,y) printf("%lld %lld\n",x,y)
#define prll3(x,y,z) printf("%lld %lld %lld\n",x,y,z)

#define pr_vec(v) for(int i=0;i<v.size();i++) cout << v[i] << " " ;

#define f_in(st) freopen(st,"r",stdin)
#define f_out(st) freopen(st,"w",stdout)

#define fr(i, a, b) for(i=a; i<=b; i++)
#define fb(i, a, b) for(i=a; i>=b; i--)
#define ASST(x, l, r) assert( x <= r && x >= l )

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

const int MAXN = 105000;

struct node {
    int next[26];
    int len;
    int sufflink;
    int num, l, r;
};

int len;
char s[MAXN];
node tree[MAXN]; 
int num;            
int suff;           
long long ans;
vi adj[ MAXN ];
viii A;
int n, q;
bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])     
            break;  
        cur = tree[cur].sufflink;
    }       
    if (tree[cur].next[let]) {  
        suff = tree[cur].next[let];
        tree[suff].num ++;
        return false;
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[num].r = pos;
    tree[num].l = pos - tree[num].len + 1; 
    tree[cur].next[let] = num;
    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }

    tree[num].num ++;
    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].sufflink = tree[cur].next[let];
            break;
        }       
    }
    return true;
}

void initTree() {
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
    tree[1].num = tree[2].num = 0; 
}

void dfs( int u ) {
    for( auto it: adj[u] ) {
        dfs(it);
        tree[u].num += tree[it].num;
     }
}

int iSA[MAXN], SA[MAXN];
int cnt[MAXN], next_gen[MAXN], lcp[ MAXN ], LCP[MAXN][22]; //internal
bool bh[MAXN], b2h[MAXN],m_arr[MAXN];

bool smaller_first_char(int a, int b){
  return s[a] < s[b];
}

void SuffixSort(int n) {
    for (int i=0; i<n; ++i){
        SA[i] = i;
    }
  sort(SA, SA + n, smaller_first_char);
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
    b2h[i] = false;
  }
  for (int h = 1; h < n; h <<= 1){
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      next_gen[i] = j;
      buckets++;
    }
    if (buckets == n) break;
    for (int i = 0; i < n; i = next_gen[i]){
      cnt[i] = 0;
      for (int j = i; j < next_gen[i]; ++j){
        iSA[SA[j]] = i;
      }
    }
    cnt[iSA[n - h]]++;
    b2h[iSA[n - h]] = true;
    for (int i = 0; i < n; i = next_gen[i]){
      for (int j = i; j < next_gen[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0){
          int head = iSA[s];
          iSA[s] = head + cnt[head]++;
          b2h[iSA[s]] = true;
        }
      }
      for (int j = i; j < next_gen[i]; ++j){
        int s = SA[j] - h;
        if (s >= 0 && b2h[iSA[s]]){
          for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
        }
      }
    }
    for (int i=0; i<n; ++i){
      SA[iSA[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    iSA[SA[i]] = i;
  }
}

void InitLCP(int n) {
  for (int i=0; i<n; ++i) 
    iSA[SA[i]] = i;
  lcp[0] = 0;
  for (int i=0, h=0; i<n; ++i) {
    if (iSA[i] > 0) {
      int j = SA[iSA[i]-1];
      while (i + h < n && j + h < n && s[i+h] == s[j+h]) 
          h++;
      lcp[iSA[i]] = h;
      if (h > 0) 
        h--;
    }
  }
}

void ConstructLCP() {
    InitLCP( len );
    for(int i = 0;i<len;++i)
    LCP[i][0] = lcp[i];
    for(int j = 1;(1<<j)<=len;++j){
        for(int i = 0;i+(1<<j)-1<len;++i){
            if(LCP[i][j-1]<=LCP[i+ ( 1<<(j-1) )][j-1])
                LCP[i][j] = LCP[i][j-1];
            else
                LCP[i][j] = LCP[i+(1<<(j-1))][j-1];
        }
    }
}

int GetLCP(int x, int y) {
    if(x == y) return len-SA[x];
    if(x > y) swap(x,y);
    int log = 0;
    while((1<<log)<=(y-x)) ++log;
    --log;
    return min(LCP[x+1][log],LCP[y-(1<<log)+1][log]);
}

bool cmp(const piii &a, const piii &b) {
    int l1, r1, l2, r2, len1, len2;
    l1 = a.ft.ft;
    r1 = a.ft.sd;
    l2 = b.ft.ft;
    r2 = b.ft.sd;
    len1 = r1 - l1 + 1;
    len2 = r2 - l2 + 1;
    int res = 0;
    int v = GetLCP(iSA[l1], iSA[l2]);
    if(v >= min(len1, len2)) {
        res = (len1 < len2);
    } else {
        res = (iSA[l1] < iSA[l2]);
    }
    return res;
}

int P[MAXN], HashF[MAXN], HashR[MAXN];
class RollingHash {
    public:
        RollingHash() {
            prime = 100001;
            mod1 = 1000000007;
            mod2 = 1897266401;
            P[0] = 1;
            for(int i=1; i<MAXN; i++) {
                P[i] = 1LL * P[i-1] * prime % mod1;
            }
        }

        void Construct() {
            HashF[0] = HashR[ len+1 ] = 0;
            for(int i=1; i<=len; i++) {
                HashF[i] = ( 1LL * HashF[i-1] * prime + s[i-1] ) % mod1;
                HashR[len-i+1] = ( 1LL * HashR[len-i+2] * prime + s[ len - i ] ) % mod1; 
            }
        }

        int GetForwardHash( int l, int r ) {
            if( l == 1 ) return HashF[r];
            int hash = HashF[r] - 1LL * HashF[l-1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        int GetBackwardHash( int l, int r ) {
            if( r == len ) return HashR[l];
            int hash = HashR[l] - 1LL * HashR[r+1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        bool IsPalin( int l, int r ) {
            if( r < l ) return true;
            return (GetForwardHash(l, r) == GetBackwardHash(l, r));
        }

    private:
        int prime, mod1, mod2;
};


int main() {

    cin >> n >> q;
    cin >> s;
    len = n;

    initTree();
    SuffixSort( len );
    ConstructLCP();
    for (int i = 0; i < len; i++) {
        addLetter(i);
    }

    for(int i=2; i<=num; i++) {
        adj[tree[i].sufflink].pb(i);
    }

    dfs(1);

    for(int i=3; i<=num; i++) {
        A.pb(mp(mp(tree[i].l, tree[i].r), tree[i].num));
    }

    sort(all(A), cmp);
    vl bs, has;
    RollingHash obj;
    obj.Construct();
    ll v = 0;
    for( auto it: A ) {
        v += it.sd;
        bs.pb( v );
        has.pb(obj.GetForwardHash(it.ft.ft+1, it.ft.sd+1));
    }
    ll k; 
    while( q-- ) {
        cin >> k;
        if( k > v ) cout << -1 << "\n";
        else {
            auto it = lower_bound(all(bs), k);
            cout << has[it-bs.begin()] << "\n";
        }
    }
    return 0;
}