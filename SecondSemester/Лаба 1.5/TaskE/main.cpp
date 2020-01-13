#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ifstream f1("problem5.in");
    ofstream f2("problem5.out");
    ll mod = 1000000007;
    ll n, m, k, l;
    f1>>n>>m>>k>>l;
    vector < vector < pair < ll, ll > > > arr1 (n, vector < pair < ll, ll > > ());
    vector <bool> terminal (n, false);
    for (ll i = 0; i < k; i++){
        ll kek;
        f1>>kek;
        kek--;
        terminal[kek] = true;
    }
    ll from, to;
    char symbol;
    for (ll i = 0; i < m; i++){
        f1>>from>>to>>symbol;
        ll numSymb = int (symbol) - int('a');
        from--;
        to--;
        arr1[from].push_back(make_pair(to, numSymb));
    }
    ////tompson
    vector < vector < ll > > arr(100, vector <ll>());
    vector <bool> terminalDka(100, false);
    set < set < ll > > was;
    queue < set < ll > > que;
    map < set < ll >, ll > index;
    que.push({0});
    was.insert({0});
    ll counter = 0;
    index[{0}] = 0;
    terminalDka[0] = terminal[0];
    while (true){
        if (que.empty()){
            break;
        }
        set <ll> now = que.front();
        que.pop();
        for (ll i = 0; i < 26; i++){
            set <ll> newSet;
            for (ll j : now){
                for (auto z : arr1[j]){
                    if (z.second == i){
                        newSet.insert(z.first);
                    }
                }
            }
            if (!newSet.empty()){
                if (was.find(newSet) == was.end()){
                    counter++;
                    was.insert(newSet);
                    index[newSet] = counter;
                    que.push(newSet);
                    for (ll j : newSet){
                        if (terminal[j]){
                            terminalDka[counter] = true;
                            break;
                        }
                    }
                }
               arr[index[now]].push_back(index[newSet]);
            }
        }
    }
    ////
    terminal.resize(terminalDka.size(), false);
    for (ll i = 0; i < terminalDka.size(); i++){
        terminal[i] = terminalDka[i];
    }
    n = 100;
    set <ll> cur, newCur;
    vector <ll> ans (n, 0), newAns(n, 0);
    cur.insert(0);
    ll answer = 0;
    for (ll i = 0; i < l; i++){
        for (set <ll>::iterator j = cur.begin(); j != cur.end(); j++){
            for (ll z = 0; z < arr[*j].size(); z++){
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
        if (terminal[*i])
            answer = (answer + ans[*i]) % mod;
    }
    f2<<answer<<endl;
    return 0;
}
