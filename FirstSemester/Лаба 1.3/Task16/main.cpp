#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ll n, k;
    ifstream f1 ("choose2num.in");
    ofstream f2 ("choose2num.out");
    f1>>n>>k;
    vector <ll> mas (k + 1);
    for (int i = 1; i <= k; i++){
        f1>>mas[i];
    }
    mas[0] = 0;
    vector < vector < ll > > c (n + 1, vector <ll> (n + 1));
    for (int i = 0; i <= n; i++){
        c[i][0] = 1;
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= k; i++){
        for (int j = mas[i - 1] + 1; j < mas[i]; j++){
            ans += c[n - j][k - i];
        }
    }
    f2<<ans;
}
