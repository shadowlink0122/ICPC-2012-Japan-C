#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <tuple>
#include <cassert>
#include <exception>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<P> vp;
#define rep(i,a,n) for(ll i = (a);i < (n);i++)
#define per(i,a,n) for(ll i = (a);i > (n);i--)
#define lep(i,a,n) for(ll i = (a);i <= (n);i++)
#define pel(i,a,n) for(ll i = (a);i >= (n);i--)
#define clr(a,b) memset((a),(b),sizeof(a))
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define sz size()
#define print(X) cout << (X) << endl
static const int INF = 1e+9+7;
ll n,m,l;
string s,t;
int d[10],dp[1010][1010];
double w[1000],v[1000];
double box[200010];
char field[200][200];
 
struct Dice{
  int over;
  int under;
  int others[4];
};
 
void rotate_side(Dice *dice){
  swap(dice->others[0],dice->others[1]);
  swap(dice->others[1],dice->others[2]);
  swap(dice->others[2],dice->others[3]);
}
 
void rotate_virtical(Dice *dice){
  swap(dice->others[0],dice->over);
  swap(dice->over,dice->others[2]);
  swap(dice->under,dice->others[2]);
}
 
// Correct orientation
void init(Dice &dice,int over,int front){
  if(dice.over != over){
    rotate_virtical(&dice);
    rotate_virtical(&dice);
    if(dice.over != over){
      while(dice.others[0] != over)rotate_side(&dice);
      rotate_virtical(&dice);
      rotate_virtical(&dice);
      rotate_virtical(&dice);
    }
  }
  while(dice.others[0] != front)rotate_side(&dice);
}
 
// Heavy bias
vi can_move(Dice dice){
  vi ans;
  vp move;
  rep(i,0,4){
    if(dice.others[i] > 3){
      move.pb(P(dice.others[i],i));
    }
  }
  sort(all(move),greater<P>());
  rep(i,0,move.sz)ans.pb(move[i].second);
  return ans;
}
 
// Find directions to go
void moving(int index,int *x,int *y){
  // cout << "move index:" << index << endl;
  if(index == 0)*x = 1,*y = 0;  // down
  if(index == 1)*x = 0,*y = 1;  // right
  if(index == 2)*x = -1,*y = 0; // up
  if(index == 3)*x = 0,*y = -1; // left
}
 
// Proceed in the specified direction
void change_rotation(Dice *dice,int x,int y){
  if(x == 0){
    if(y == 1){
      init(*dice,dice->others[3],dice->others[0]);
    }else{
      init(*dice,dice->others[1],dice->others[0]);
    }
  }
  if(y == 0){
    if(x == 1){
      rotate_virtical(dice);
    }else{
      rotate_virtical(dice);
      rotate_virtical(dice);
      rotate_virtical(dice);
    }
  }
}
 
// For debug
void print_dice(Dice &dice){
  cout << "over:" << dice.over << endl;
  cout << "under:" << dice.under << endl;
  rep(i,0,4)cout << dice.others[i] << " ";
  puts("");
}
 
// Depth first search
void dfs(Dice *dice,int x,int y){
  bool f = false;
  int can_movex = 0,can_movey = 0;
  Dice now = *dice;
  vi move = can_move(*dice);
  // puts("Now:");
  // print_dice(now);
  // puts("-------------");
  rep(i,0,move.sz){
    moving(move[i],&can_movex,&can_movey);
    if(field[x][y] > field[x+can_movex][y+can_movey]){
      // 回転させたものを渡す
      // cout << "move index:" << i << endl;
      change_rotation(dice,can_movex,can_movey);
      // print_dice(*dice);
      dfs(dice,x+can_movex,y+can_movey);
      return;
    }
  }
  dp[x][y] = now.over;
  field[x][y]++;
}
 
int main(){
  Dice dice;
  dice.over = 1;
  dice.under = 6;
  dice.others[0] = 2;
  dice.others[1] = 3;
  dice.others[2] = 5;
  dice.others[3] = 4;
  while(cin >> n && n){
    clr(d,0);
    clr(dp,0);
    clr(field,0);
    rep(i,0,n){
      clr(d,0);
      cin >> m >> l;
      init(dice,m,l);
      // puts("===================");
      dfs(&dice,10,10);
      rep(i,0,100)rep(j,0,100)d[dp[i][j]]++;
      // puts("");
      // rep(i,0,20){
      //   rep(j,0,20){
      //     if(field[i][j])cout << "#";
      //     else cout << "_";
      //   }
      //   puts("");
      // }
    }
    lep(i,1,6){
      cout << d[i];
      if(i == 6)break;
      cout << " ";
    }
    puts("");
  }
  return 0;
}
