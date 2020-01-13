#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ifstream f1("problem4.in");
    ofstream f2("problem4.out");
    ll mod = 1000000007;
    ll n, m, k, l;
    f1>>n>>m>>k>>l;
    vector < vector < ll > > arr (n, vector <ll> (26, -1));
    vector <ll> ans (n, 0), newAns(n, 0);
    vector <ll> terminal;
    for (ll i = 0; i < k; i++){
        ll kek;
        f1>>kek;
        kek--;
        terminal.push_back(kek);
    }
    sort (terminal.begin(), terminal.end());
    ll from, to;
    char symbol;
    for (ll i = 0; i < m; i++){
        f1>>from>>to>>symbol;
        ll numSymb = int (symbol) - int('a');
        from--;
        to--;
        arr[from][numSymb] = to;
    }
    set <ll> cur, newCur;
    cur.insert(0);
    ll answer = 0;
    for (ll i = 0; i < l; i++){
        for (set <ll>::iterator j = cur.begin(); j != cur.end(); j++){
            for (ll z = 0; z < arr[*j].size(); z++){
                if (arr[*j][z] == -1) continue;
                newAns[arr[*j][z]] = (newAns[arr[*j][z]] + (ans[*j] == 0 ? 1 : ans[*j])) % mod;
                newCur.insert(arr[*j][z]);
            }
        }
        for (ll j = 0; j < n; j++){
            ans[j] = newAns[j];
            newAns[j] = 0;
        }
        cur = newCur;
        newCur.clear();
    }
    for (set <ll>::iterator i = cur.begin(); i != cur.end(); i++){
        if (find(terminal.begin(), terminal.end(), *i) == terminal.end()){
            continue;
        }
        answer = (answer + ans[*i]) % mod;
    }
    f2<<answer<<endl;
    return 0;
}
