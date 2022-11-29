#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cassert>
#define PB push_back
#define MP make_pair
#define sz(v) (in((v).size()))
#define forn(i,n) for(in i=0;i<(n);++i)
#define forv(i,v) forn(i,sz(v))
#define fors(i,s) for(auto i=(s).begin();i!=(s).end();++i)
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long in;
typedef vector<in> VI;
typedef vector<VI> VVI;
in dct=0;
map<in,in> mar;
set<in> td;
void proc(in id){
  auto it=mar.find(id);
  auto it2=it;
  ++it2;
  mar.erase(it);
  if(it2!=mar.end() && it2!=mar.begin()){
    it=it2;
    --it;
    if(it2->second>it->second)
      td.insert(it2->first);
    else{
      if(td.count(it2->first))
    td.erase(it2->first);
    }
  }
}
VI otd;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  in n;
  cin>>n;
  in ta;
  forn(i,n){
    cin>>ta;
    mar[i]=ta;
    if(i>0 && mar[i]>mar[i-1])
      td.insert(i);
  }
  while(!td.empty()){
    dct++;
    otd.clear();
    fors(i,td)
      otd.PB(*i);
    td.clear();
    reverse(all(otd));
    forv(i,otd){
      proc(otd[i]);
    }
  }
  cout<<dct<<endl;
  return 0;
}