#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll maxN = 50001, maxAlph = 26;

ll n, m, k;

vector <bool> terminal (maxN, false);
vector < vector < ll > > arr (maxN, vector <ll> (maxAlph, 0));
vector < vector < vector < ll > > > arrRev (maxN, vector < vector < ll > > (maxAlph, vector <ll> (0)));

vector <ll> classes (maxN);
vector < unordered_set < ll > > P;
unordered_set <ll> F;
unordered_set <ll> NF;
unordered_set <ll> newSet;

void findClasses(){
    for (ll i = 0; i < n; i++){
        if (terminal[i]){
            F.insert(i);
            classes[i] = 0;
        } else {
            NF.insert(i);
            classes[i] = 1;
        }
    }
    //разбили на два класса эквивалентности
    P.push_back(F);
    P.push_back(NF);
    queue < pair < ll, ll > > que;
    for (ll i = 0; i < maxAlph; i++){
        que.push(make_pair(0, i));
        que.push(make_pair(1, i));
    }
    //по всем буквам пройтись и закинуть переходы
    while (!que.empty()){
        auto now = que.front();
        que.pop();
        auto C = P[now.first]; //нынешний класс эквивалентности
        unordered_map < ll, vector < ll > > involved;
        for (auto q : C){
            for (auto r : arrRev[q][now.second]){
                auto i = classes[r];
                involved[i].push_back(r);
            }
        }
        //involved - те что переходят из состояния по символу в С
        //надо разбить наш класс жквивалентности R на R1 и R2
        //R1 входит другой не
        for (auto q : involved){
            if (!q.second.empty()){
                if (involved[q.first].size() < P[q.first].size()){
                    ll j = P.size();
                    P.push_back(newSet);
                    for (auto r : involved[q.first]){
                        P[q.first].erase(r);
                        P[j].insert(r);
                    }
                    if (P[q.first].size() < P[j].size()){
                        swap(P[q.first], P[j]);
                    }
                    for (ll r : P[j]){
                        classes[r] = j;
                    }
                    for (ll r = 0; r < maxAlph; r++){
                        que.push(make_pair(j, r));
                    }
                }
            }
        }
    }
}

vector <bool> used (maxN);
void dfs (ll now){
    if (now == 0){
        return;
    }
    used[now] = true;
    for (ll i = 0; i < maxAlph; i++){
        if (!used[arr[now][i]]){
            dfs(arr[now][i]);
        }
    }
}

vector < vector < ll > > newArr (maxN, vector <ll> (maxAlph, -1));
vector <ll> index(maxN);
vector < pair < pair < ll, ll >, ll > > newArrSymb;
ll ansN = 0;
void fillNewArrSymb(ll now){
    if (index[now] == 0){
        ansN++;
        index[now] = ansN;
        for (ll i = 0; i < maxAlph; i++){
            if (newArr[now][i] != -1){
                fillNewArrSymb(newArr[now][i]);
                newArrSymb.push_back(make_pair(make_pair(index[now], index[newArr[now][i]]), i));
            }
        }
    }
}

int main()
{
    ifstream f1("minimization.in");
    ofstream f2("minimization.out");
    f1>>n>>m>>k;
    n++;
    for (ll i = 0; i < k; i++){
        ll now;
        f1>>now;
        terminal[now] = true;
    }
    for (ll i = 0; i < m; i++){
        ll from, to;
        char symbol;
        f1>>from>>to>>symbol;
        arr[from][int(symbol) - int('a')] = to;
    }
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < maxAlph; j++){
            arrRev[arr[i][j]][j].push_back(i);
        }
    }
    dfs(1);
    findClasses();
    for (ll i = 1; i < n; i++){
        if (classes[i] != classes[0] && used[i]){
            for (ll j = 0; j < maxAlph; j++){
                if (classes[arr[i][j]] != classes[0] && used[arr[i][j]]){
                    newArr[classes[i]][j] = classes[arr[i][j]];
                }
            }
        }
    }
    fillNewArrSymb(classes[1]);
    set <ll> newTerminal;
    for (ll i = 0; i < n; i++){
        if (terminal[i] && classes[i] != classes[0] && used[i]){
            newTerminal.insert(index[classes[i]]);
        }
    }
    ll ansK = newTerminal.size();
    ll ansM = newArrSymb.size();
    f2<<ansN<<' '<<ansM<<' '<<ansK<<endl;
    for (ll i : newTerminal){
            f2<<i<<' ';
    }
    f2<<endl;
    for (ll i = 0; i < ansM; i++){
        f2<<newArrSymb[i].first.first<<' '<<newArrSymb[i].first.second<<' '<<char (newArrSymb[i].second + int('a'))<<endl;
    }
}
