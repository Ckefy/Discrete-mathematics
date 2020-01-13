#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ifstream f1 ("brackets2num.in");
    ofstream f2 ("brackets2num.out");
    string s;
    f1>>s;
    ll n = s.length()/2;
    vector < vector < ll > > d (2 * n + 1, vector <ll> (2 * n + 1));
    d[0][0] = 1;
    for (int i = 1; i <= 2 * n; i ++){
        d[0][i] = 0;
    }
    for (int i = 1; i <= 2 * n; i++){
        for (int j = 0; j <= 2 * n; j++){
            if (j > n){
                d[i][j] = 0;
                continue;
            }
            if (j == 0){
                d[i][j] = d[i - 1][j + 1];
                continue;
            }
            d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
        }
    }
    ll k = 0, dep = 0;
    for (int i = 0; i < 2 * n; i++){
        if (s[i] == '('){
                dep++;
            }
        else {
            if (dep + 1 >= 0){
                k += d[2 *  n - i - 1][dep + 1];
            }
            dep--;
        }
    }
    f2<<k<<endl;
    f1.close();
    f2.close();
}
