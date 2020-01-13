#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    string word;
    ifstream f1("problem2.in");
    ofstream f2("problem2.out");
    f1>>word;
    ll n, m, k;
    f1>>n>>m>>k;
    vector < vector < vector < ll > > > arr;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
		arr[i].resize(26);
	}
    set <ll> terminal;
    for (ll i = 0; i < k; i++){
        ll now;
        f1>>now;
        now--;
        terminal.insert(now);
    }
    ll from, to;
    char symbol;
    for (ll i = 0; i < m; i++){
        f1>>from>>to>>symbol;
        ll numSymb = int (symbol) - int('a');
        from--;
        to--;
        arr[from][numSymb].push_back(to);
    }
    set <ll> cur;
    set <ll> newCur;
    cur.insert(0);
    for (ll i = 0; i < word.length(); i++){
        for (set <ll> :: iterator j = cur.begin(); j != cur.end(); j++){
            for (ll k = 0; k < arr[*j][int(word[i]) - 'a'].size(); k++){
                newCur.insert(arr[*j][int(word[i]) - 'a'][k]);
            }
        }
        cur = newCur;
        newCur.clear();
    }
    for (set <ll> :: iterator i = cur.begin(); i != cur.end(); i++){
        if (terminal.find(*i) != terminal.end()){
            f2<<"Accepts";
            return 0;
        }
    }
    f2<<"Rejects";
}
