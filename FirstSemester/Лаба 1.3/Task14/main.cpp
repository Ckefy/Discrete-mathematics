#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ifstream f1 ("perm2num.in");
    ofstream f2 ("perm2num.out");
    ll n;
    f1>>n;
    vector <ll> mas (n);
    for (int i = 0; i < n; i++){
        f1>>mas[i];
    }
    vector <ll> f (n);
    f[0] = 1;
    for (int i = 1; i < n; i++){
        f[i] = f[i - 1] * i;
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int k = 0;
        for (int j = i + 1; j < n; j++){
            if (mas[j] < mas[i]){
                k++;
            }
        }
        ans += k * f[n - i - 1];
    }
    f2<<ans<<endl;
    f1.close();
    f2.close();
}
