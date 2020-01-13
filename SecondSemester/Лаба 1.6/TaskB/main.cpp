#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

ll n;
vector <bool> eborn (26, false);
vector < pair < int, string > > arr;

bool check (string now){
    for (ll i = 0; i < now.length(); i++){
        if (!eborn[int(now[i]) - int('A')]){
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream f1 ("epsilon.in");
    ofstream f2 ("epsilon.out");
    f1>>n;
    char start;
    f1>>start;
    char now;
    string garbage, result;
    for (ll i = 0; i < n; i++){
        f1>>now>>garbage;
        getline(f1, result); //в нуле лежит пробел, либо размер 0
        if (result.length() == 0){
            eborn[int(now) - int('A')] = true;
            continue;
        }
        arr.pb(mp(int(now) - int('A'), result.substr(1)));
    }
    bool flag = true;
    while (flag){
        flag = false;
        for (ll i = 0; i < arr.size(); i++){
            if (eborn[arr[i].first]){
                continue;
            }
            if (check(arr[i].second)){
                eborn[arr[i].first] = true;
                flag = true;
            }
        }
    }
    for (ll i = 0; i < 26; i++){
        if (eborn[i]){
            f2<<char (i + int ('A'))<<' ';
        }
    }
}
