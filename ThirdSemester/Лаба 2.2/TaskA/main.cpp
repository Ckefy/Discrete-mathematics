#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    ifstream f1("schedule.in");
    f1>>n;
    vector < pair < ll, ll > > a;
    set <ll> numbers;
    for (int i = 0; i < n; i++){
        ll d, w;
        f1>>d>>w;
        w *= (-1);
        a.push_back(make_pair(w, d));
        numbers.insert(i + 1);
    }
    sort (a.begin(), a.end());
    ll ans = 0;
    for (int i = 0; i < n; i++){
        set<ll>::iterator it = numbers.lower_bound(a[i].second);
        if (*it == a[i].second){
            numbers.erase(it);
        } else if (it == numbers.begin()){
            ans += a[i].first;
        } else {
            it--;
            numbers.erase(it);
        }
    }
    ans *= (-1);
    ofstream f2("schedule.out");
    f2<<ans;
}
