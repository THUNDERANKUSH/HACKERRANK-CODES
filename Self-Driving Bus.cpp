#include<iostream>
#include<vector>
using namespace std;

typedef long long int lli;
typedef pair<lli,lli> ii;
typedef vector<lli> vi;
typedef vector<vi> vii;

const lli MAXN = 200200;
lli par[MAXN], upr[MAXN],dnr[MAXN];
lli run_upr[MAXN], run_dnr[MAXN], grand[MAXN];
vii G(MAXN);

void set_parents(lli m,lli a,lli b, lli p){
  upr[m] = max(m,upr[p]);
  dnr[m] = min(m,dnr[p]);
  par[m] = p;
  grand[m] = grand[p]; 
  for(auto it = G[m].begin() ; it != G[m].end(); it++){
    if((*it) < a || (*it) >= b || (*it) == p) continue;
    set_parents(*it, a, b, m);
  }
}

lli middle_case(lli m, lli a, lli b){
  run_upr[m] = run_dnr[m] = m;
  lli aux;
  for(aux = m ; aux < b && grand[aux] == m ; aux++);
  b = aux;
  for(aux = m ; aux >= a && grand[aux] == m ; aux--);
  a = aux + 1;

  for(lli i = m + 1 ; i < b ; i++){
    run_upr[i] = max(run_upr[i-1], upr[i]);
    run_dnr[i] = min(run_dnr[i-1], dnr[i]);
  }

  for(lli i = m - 1 ; i >= a ; i--){
    run_upr[i] = max(run_upr[i+1], upr[i]);
    run_dnr[i] = min(run_dnr[i+1], dnr[i]);
  }
  lli total = 0; // {m}
  // Contamos [i,d] con i <= m/2, d>= m/2
  for(lli d = m, l = m + 1, r = m+ 1, ct = 0; d < b ; d++){
    if(d != run_upr[d]) continue;
    for(; l - 1>= a && d >= run_upr[l- 1] ;l--){
      if(l-1 == run_dnr[l-1]) ct++;
    }
    for(; r - 1> run_dnr[d] && r > l; r--){
      if(r - 1 == run_dnr[r-1]) ct--;
    }
    total += ct;
  }
  return total;
}

lli solve(lli a, lli b){
  if(a == b){
    return 0;
  }
  if(a + 1 == b){
    return 1;
  }
  lli m = (a+b)/2;
  lli x,y,z;
  upr[m] = par[m] = dnr[m] = grand[m] = m;
  set_parents(m,a,b,m);
  x = middle_case(m,a,b);
  y = solve(a,m);
  z = solve(m + 1,b);
  return (x+y+z);
}

int main(){
  lli n, a,b;
  cin >> n;
  for(int i = 1 ; i<n;i++){
    cin >> a >> b;
    a--;
    b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  cout << solve(0,n) << endl;
  return 0;
}
