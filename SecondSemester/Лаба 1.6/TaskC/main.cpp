#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;

ll n;
vector <bool> born (26, false);
vector <bool> far (26, false);
vector <bool> del (26, false);
vector < pair < int, string > > arr;
vector <bool> used (26, false);

bool check (string now){
    for (ll i = 0; i < now.length(); i++){
        if (now[i] <= 'Z' && now[i] >= 'A' && !born[int(now[i]) - int('A')])
            return false;
    }
    return true;
}

int main()
{
    ifstream f1 ("useless.in");
    ofstream f2 ("useless.out");
    f1>>n;
    char start;
    f1>>start;
    used[start - int('A')] = true;
    char now;
    string garbage, result;
    for (ll i = 0; i < n; i++){
        f1>>now>>garbage;
        getline(f1, result);
        used[int(now) - int('A')] = true;
        if (result.length() == 0){
            born[int(now) - int('A')] = true;
            continue;
        }
        for (ll j = 1; j < result.length(); j++){
            if (result[j] >= 'A' && result[j] <= 'Z'){
                used[int(result[j]) - int('A')] = true;
            }
        }
        arr.pb(mp(int(now) - int('A'), result.substr(1)));
        for (ll j = 1; j < result.length(); j++){
            if (result[j] >= 'A' && result[j] <= 'Z'){
                break;
            } else if (j == result.length() - 1){
                born[int (now) - int('A')] = true;
            }
        }
    }

    bool flag = true;
    while (flag){
        flag = false;
        for (ll i = 0; i < arr.size(); i++){
            if (born[arr[i].first]){
                continue;
            }
            if (check(arr[i].second)){
                born[arr[i].first] = true;
                flag = true;
            }
        }
    }

    vector < pair < int, string > > arr1;
    bool flag1 = false;
    for (ll i = 0; i < arr.size(); i++){
        flag1 = false;
        if (!born[arr[i].first]){
            continue;
        }
        for (ll j = 0; j < arr[i].second.length(); j++){
            if (arr[i].second[j] >='A' && arr[i].second[j] <='Z' && !born[int (arr[i].second[j]) - int ('A')]){
                flag1 = true;
                break;
            }
        }
        if (flag1) continue;
        arr1.push_back(arr[i]);
    }
    arr.resize(0);
    for (ll i = 0; i < arr1.size(); i++){
        //cout<<arr1[i].first<<' '<<arr1[i].second<<endl;
        arr.push_back(arr1[i]);
    }



    flag = true;
    far[int(start) - int('A')] = true;
    while (flag){
        flag = false;
        for (ll i = 0; i < arr.size(); i++){
            if (far[arr[i].first]){
                for (ll j = 0; j < arr[i].second.length(); j++){
                    if (arr[i].second[j] >='A' && arr[i].second[j] <='Z' && !far[int (arr[i].second[j]) - int ('A')]){
                        far[int (arr[i].second[j]) - int ('A')] = true;
                        flag = true;
                    }
                }
            }
        }
    }

    vector < pair < int, string > > arr2;
    flag1 = false;
    for (ll i = 0; i < arr.size(); i++){
        flag1 = false;
        if (!far[arr[i].first]){
            continue;
        }
        for (ll j = 0; j < arr[i].second.length(); j++){
            if (arr[i].second[j] >='A' && arr[i].second[j] <='Z' && !far[int (arr[i].second[j]) - int ('A')]){
                flag1 = true;
                break;
            }
        }
        if (flag1) continue;
        arr2.push_back(arr[i]);
    }
    arr.resize(0);
    for (ll i = 0; i < arr2.size(); i++){
        //cout<<arr2[i].first<<' '<<arr2[i].second<<endl;
        arr.push_back(arr2[i]);
    }
    vector <bool> used1(26, false);
    for (ll i = 0; i < arr.size(); i++){
        result = arr[i].second;
        for (ll j = 0; j < result.length(); j++){
            if (result[j] >= 'A' && result[j] <= 'Z'){
                used1[int(result[j]) - int('A')] = true;
            }
        }
        used1[arr[i].first] = true;
    }
    for (ll i = 0; i < 26; i++){
        if (used[i] && !used1[i]){
            f2<<char (i + int ('A'))<<' ';
        }
    }
}
