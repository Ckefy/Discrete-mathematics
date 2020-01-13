#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back

using namespace std;

ll n;
vector < vector < pair < ll, char > > > arr (26);
string need;

bool ans (ll to, ll index){
    if (to == -1){
        if (index == need.length()){
            return true;
        }
        return false;
    }
    for (ll i = 0; i < arr[to].size(); i++){
        if (arr[to][i].second == need[index]){
            if (ans(arr[to][i].first, index + 1)){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ifstream f1("automaton.in");
    ofstream f2("automaton.out");
    ll m;
    char s;
    f1>>n>>s;
    char term;
    string garbage, result;
    for (ll i = 0; i < n; i++){
        f1>>term>>garbage>>result;
        if (result.length() == 1){
            arr[int (term) - int('A')].pb(mp (-1, result[0]));
        } else {
            arr[int(term) - int('A')].pb(mp (int (result[1]) - int ('A'), result[0]));
        }
    }
    ll start = int(s) - int('A');
    f1>>m;
    for (ll i = 0; i < m; i++){
        f1>>need;
        if (ans(start, 0)){
            f2<<"yes"<<endl;
        } else {
            f2<<"no"<<endl;
        }
    }
}
