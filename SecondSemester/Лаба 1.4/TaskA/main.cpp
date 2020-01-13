#include <bits/stdc++.h>
#define ll int

using namespace std;

int main()
{
    ifstream f1 ("exam.in");
    ofstream f2 ("exam.out");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k, n;
    f1>>k>>n;
    ll p, m, ans = 0;
    for (int i = 0; i < k; i++){
        f1>>p>>m;
        ans += (p * m);
    }
    double ans1 = double (ans) / double(n);
    ans1 /= double (100);
    setprecision(5);
    f2<<fixed<<ans1;
    f1.close();
    f2.close();
}
