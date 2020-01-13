#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    string word;
    ifstream f1("problem1.in");
    ofstream f2("problem1.out");
    f1>>word;
    ll n, m, k;
    f1>>n>>m>>k;
    vector < vector < ll > > arr (n, vector <ll> (26, -1));
    vector <ll> terminal(k);
    for (ll i = 0; i < k; i++){
        f1>>terminal[i];
        terminal[i]--;
    }
    ll from, to;
    char symbol;
    for (ll i = 0; i < m; i++){
        f1>>from>>to>>symbol;
        ll numSymb = int (symbol) - int('a');
        from--;
        to--;
        arr[from][numSymb] = to;
    }
    char curChar = word[0];
    ll i = 0;
    ll curPoint = 0;
    while (true){
        ll curNumSymb = int(curChar) - int('a');
        to = arr[curPoint][curNumSymb];
        i++;
        if (to == -1){
            f2<<"Rejects";
            return 0;
        }
        curPoint = to;
        if (i == word.length()){
            break;
        }
        curChar = word[i];
    }
    for (ll i = 0; i < k; i++){
        if (terminal[i] == curPoint){
            f2<<"Accepts";
            return 0;
        }
    }
    f2<<"Rejects";
}
