#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <bool> terminalFir, terminalSec, used;
vector < vector < ll > > arrFir, arrSec;

bool dfs (ll first, ll second){
    if (used[first]){
        return true;
    } else {
        used[first] = true;
    }
    if ((!terminalFir[first] && terminalSec[second]) || (terminalFir[first] && !terminalSec[second])){
        return false;
    }
    for (int i = 0; i < 26; i++){
        ll toFir = arrFir[first][i], toSec = arrSec[second][i];
        if ((toFir == 0 && toSec != 0) || (toFir != 0 && toSec == 0)){
            return false;
        }
        if (!used[toFir]){
            if (!dfs(toFir, toSec)){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    ifstream f1 ("isomorphism.in");
    ofstream f2 ("isomorphism.out")
    ll n, m, k;
    cin>>n>>m>>k;
    terminalFir.resize(n, false);
    used.resize(n, false);
    arrFir.resize(n, vector <ll> (26, 0));
    for (ll i = 0; i < k; i++){
        ll now;
        cin>>now;
        terminalFir[--now] = true;
    }
    for (ll i = 0; i < m; i++){
        ll now1, now2;
        char symb;
        cin>>now1>>now2>>symb;
        arrFir[--now1][int(symb) - int('a')] = (--now2);
    }
    cin>>n>>m>>k;
    if (n != used.size()){
        cout<<"NO";
        return 0;
    }
    terminalSec.resize(n, false);
    arrSec.resize(n, vector <ll> (26, 0));
    for (ll i = 0; i < k; i++){
        ll now;
        cin>>now;
        terminalSec[--now] = true;
    }
    for (ll i = 0; i < m; i++){
        ll now1, now2;
        char symb;
        cin>>now1>>now2>>symb;
        arrSec[--now1][int(symb) - int('a')] = (--now2);
    }
    cout<<(dfs(0, 0) ? "YES" : "NO")<<endl;
}
