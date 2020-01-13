#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector <ll> master;

ll findMaster (ll now){
    if (now == master[now]){
        return now;
    } else {
        master[now] = findMaster(master[now]);
        return master[now];
    }
}

void connect (ll from, ll to){
    master[findMaster(to)] = findMaster(from);
}

int main()
{
    ifstream f1("destroy.in");
    ofstream f2("destroy.out");
    vector < pair < pair < ll, ll >, pair < ll, ll > > > g;
    vector <ll> value;
    ll n, m, s;
    f1>>n>>m>>s;
    for (ll i = 0; i < n; i++){
        master.push_back(i);
    }
    for (ll i = 0; i < m; i++){
        ll a, b, w;
        f1>>a>>b>>w;
        a--; b--;
        value.push_back(w);
        g.push_back(make_pair(make_pair (w, i), make_pair(a, b)));
    }
    sort(g.rbegin(), g.rend());
    vector <ll> nonMst;
    for (ll i = 0; i < m; i++){
        pair <ll, ll> edge = g[i].second;
        ll w = g[i].first.first;
        ll number = g[i].first.second;
        ll from = edge.first;
        ll to = edge.second;
        if (findMaster(from) != findMaster(to)){
            connect(from, to);
        } else {
            nonMst.push_back(number);
        }
    }
    reverse(nonMst.begin(), nonMst.end());
    ll temp = 0;
    vector <ll> answer;
    for (ll i = 0; i < nonMst.size(); i++){
        if (temp + value[nonMst[i]] <= s){
            temp += value[nonMst[i]];
            answer.push_back(nonMst[i]);
        } else{
            break;
        }
    }
    f2<<answer.size()<<endl;
    for (ll i = 0; i < answer.size(); i++){
        f2<<answer[i] + 1<<' ';
    }
}
