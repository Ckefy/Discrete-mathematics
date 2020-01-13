#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

ll const maxN = 100;

struct myType {
    char first, second;
    bool isTerm;
    myType(){}
    myType (char first, char second, bool isTerm) : first(first), second(second), isTerm(isTerm){};
};

ll dp[26][maxN][maxN];
vector < vector < myType > > rules;
ll mod = 1000000007, n;
string need;

ll getAns (ll now, ll l, ll r){
    if (dp[now][l][r] == -1){
        ll ans = 0;
        for (ll i = 0; i < rules[now].size(); i++){
            myType current = rules[now][i];
            if (!current.isTerm){
                for (ll j = l + 1; j < r; j++){
                    ans = (getAns(current.first - 'A', l, j) * getAns(current.second - 'A', j, r) + ans) % mod;
                }
            } else {
                if ((l + 1 == r) && (need[l] == current.first)){
                    ans++;
                    ans %= mod;
                }
            }
        }
        dp[now][l][r] = ans;
    }
    return dp[now][l][r];
}

int main()
{
    ifstream f1 ("nfc.in");
    ofstream f2 ("nfc.out");
    f1>>n;
    char start;
    f1>>start;
    rules.resize(26);
    memset(dp, -1, sizeof(dp));
    char now;
    string garbage, result;
    for (ll i = 0; i < n; i++){
        f1>>now>>garbage;
        getline(f1, result);
        myType* newElem = new myType(result[1], result.length() >= 3 ? result[2] : 'a', result.length() >= 3 ? false : true);
        rules[int(now) - int('A')].pb(*newElem);
    }
    f1>>need;
    f2<<getAns(int(start) - int('A'), 0, need.length())<<endl;
}
