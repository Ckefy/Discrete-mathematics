#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream f1("equivalence.in");
ofstream f2("equivalence.out");

class Minim{
    private:
        ll maxN = 1001, maxAlph = 26;
        ll n, m, k;
        vector < vector < ll > > newArr;
        vector <ll> index;
        vector <bool> terminal;
        vector < vector < ll > > arr;
        vector < vector < vector < ll > > > arrRev;
        vector <ll> classes;
        vector < unordered_set < ll > > P;
        unordered_set <ll> F;
        unordered_set <ll> NF;
        unordered_set <ll> newSet;
        vector <bool> used;

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

    public:
        vector < pair < pair < ll, ll >, ll > > newArrSymb;
        set <ll> newTerminal;
        ll ansN = 0;
        ll ansK = 0;
        ll ansM = 0;

        void initialize(){
            newArr.resize(maxN, vector <ll> (maxAlph, -1));
            index.resize(maxN);
            terminal.resize(maxN, false);
            arr.resize(maxN, vector <ll> (maxAlph, 0));
            arrRev.resize(maxN, vector < vector < ll > > (maxAlph, vector <ll> (0)));
            classes.resize(maxN);
            used.resize(maxN);
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
            for (ll i = 0; i < n; i++){
                if (terminal[i] && classes[i] != classes[0] && used[i]){
                    newTerminal.insert(index[classes[i]]);
                }
            }
            ansK = newTerminal.size();
            ansM = newArrSymb.size();
        }

};

class Isomorphism{
    private:
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
    public:
        vector <bool> terminalFir, terminalSec, used;
        vector < vector < ll > > arrFir, arrSec;

        bool initialize(ll n1, ll m1, ll k1, ll n2, ll m2, ll k2, vector < pair < pair < ll, ll >, ll > > first, vector < pair < pair < ll, ll >, ll > > second, set <ll> firstT, set <ll> secondT){
            ll n, m, k;
            n = n1;
            m = m1;
            k = k1;
            terminalFir.resize(n, false);
            used.resize(n, false);
            arrFir.resize(n, vector <ll> (26, 0));
            for (auto i : firstT){
                 ll smth = i;
                 terminalFir[--smth] = true;
            }
            for (ll i = 0; i < m; i++){
                ll now1 = first[i].first.first;
                ll now2 = first[i].first.second;
                char symb = char (first[i].second + int('a'));
                arrFir[--now1][int(symb) - int('a')] = (--now2);
            }
            n = n2;
            m = m2;
            k = k2;
            if (n != used.size()){
                f2<<"NO";
                return false;
            }
            terminalSec.resize(n, false);
            arrSec.resize(n, vector <ll> (26, 0));
            for (auto i : secondT){
                ll smth = i;
                 terminalSec[--smth] = true;
            }
            for (ll i = 0; i < m; i++){
                ll now1 = second[i].first.first;
                ll now2 = second[i].first.second;
                char symb = char (second[i].second + int('a'));
                arrSec[--now1][int(symb) - int('a')] = (--now2);
            }
            return true;
        }

        void checkIso(){
                f2<<(dfs(0, 0) ? "YES" : "NO")<<endl;
        }
};

int main()
{
    Minim t1;
    t1.initialize();
    Minim t2;
    t2.initialize();
    Isomorphism ans;
    bool answer = ans.initialize(t1.ansN, t1.ansM, t1.ansK, t2.ansN, t2.ansM, t2.ansK, t1.newArrSymb, t2.newArrSymb, t1.newTerminal, t2.newTerminal);
    if (answer){
        ans.checkIso();
    }
}
