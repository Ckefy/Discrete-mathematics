#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

struct myType{
    ll first;
    bool isTerm;
};

map <ll, vector < vector < myType > > > rules;
ll dp[1001][100][100];
string need;
ll freeInd = 26;
set <ll> del;

void makeShort(){
    map <ll, vector < vector < myType > > > arr;
    for (auto i : rules){
        ll now = i.first;
        for (auto j : rules[now]){
            if (j.size() > 2){
                ll to = now;
                for (ll k = 0; k < j.size() - 2; k++){
                    arr[to].pb({j[k], {++freeInd, false}});
                    to = freeInd;
                }
                arr[to].pb({j[j.size() - 2], j[j.size() - 1]});
            } else {
                arr[now].pb(j);
            }
        }
    }
    rules = arr;
}

void findEpsBorning(){
    ll old = -1;
    while ((ll) del.size() > old){
        old = del.size();
        for(auto i : rules){
            bool willDelete = false;
            ll now = i.first;
            for (auto j : rules[now]){
                bool wasntTerm = true;
                for (auto vert : j){
                    if (vert.isTerm){
                        wasntTerm = false;
                    } else {
                        wasntTerm &= del.count(vert.first);
                    }
                }
                willDelete |= wasntTerm;
            }
            if (willDelete){
                del.insert(now);
            }
        }
    }
}

ll start;
ll newS = 0;

void makeWithoutEps(){
    findEpsBorning();
    map <ll, vector < vector < myType > > > arr;
    for (auto i : rules){
        ll now = i.first;
        for (auto j : rules[now]){
            if (j.size() == 1){
                arr[now].pb(j);
            } else if (j.size() == 2){
                if (del.count(j[0].first) && del.count(j[1].first)){
                    arr[now].pb(j);
                    arr[now].pb({j[0]});
                    arr[now].pb({j[1]});
                } else if (del.count(j[0].first)){
                    arr[now].pb({j[1]});
                    arr[now].pb({j[0], j[1]});
                } else if (del.count(j[1].first)){
                    arr[now].pb({j[0]});
                    arr[now].pb({j[0], j[1]});
                } else {
                    arr[now].pb(j);
                }
            }
        }
    }
    if (del.count(start)){
        arr[1000].pb({{start, false}});
        arr[1000].pb ({{}});
        start = 1000;
    }
    rules = arr;
}

ll getAns (ll now, ll l, ll r){
    if ((dp[now][l][r] == -2) || (l >= r)){
        return 0;
    }
    if (dp[now][l][r] == -1){
            ll ans = 0;
            dp[now][l][r] = -2;
            for (auto i : rules[now]){
                if (i.size() == 2){
                    if (i[0].isTerm && i[1].isTerm){
                            if (l + 2 == r && need[l] == i[0].first && need[l + 1] == i[1].first)
                            ans = 1;

                    } else if (i[0].isTerm){
                        if (need[l] == i[0].first){
                            ans |= getAns(i[1].first, l + 1, r);
                        }
                    } else if (i[1].isTerm){
                        if (need[r - 1] == i[1].first){
                            ans |= getAns(i[0].first, l, r - 1);
                        }
                    } else {
                        for (ll j = l + 1; j < r; j++){
                            ans |= getAns(i[0].first, l, j) * getAns(i[1].first, j, r);
                        }
                    }
                } else if (i.size() == 1){
                    if (i[0].isTerm){
                        if (l + 1 == r && need[l] == i[0].first){
                            ans = 1;
                        }
                    } else {
                        ans |= getAns(i[0].first, l, r);
                    }
                }
            }
            dp[now][l][r] = ans;
        }
        return dp[now][l][r];
}

int main()
{
    ifstream f1 ("cf.in");
    ofstream f2 ("cf.out");
    memset(dp, -1, sizeof(dp));
    ll n;
    char startc;
    f1>>n>>startc;
    start = startc - 'A';
    char now;
    string garbage, result;
    for (ll i = 0; i < n; i++){
        f1>>now>>garbage;
        getline(f1, result);
        vector <myType> tmp;
        for (ll j = 0; j < result.length(); j++){
            if (result[j] >= 'a' && result[j] <= 'z'){
                tmp.pb({result[j], true});
            } else if (result[j] >= 'A' && result[j] <= 'Z'){
                tmp.pb({result[j] - 'A', false});
            }
        }
        rules[now - 'A'].pb(tmp);
    }
    f1>>need;
    makeShort();
    makeWithoutEps();
    f2<<(getAns(start, 0, need.length()) ? "yes" : "no")<<endl;
}
