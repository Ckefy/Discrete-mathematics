#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream f1 ("lottery.in");
    ofstream f2 ("lottery.out");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    f1>>n>>m;
    double a, b, aold = 0, bold = 0;
    f1>>aold>>bold;
    double probablity = (aold - 1) / aold;
    double ans = 0;
    for (int i = 1; i < m; i++){
        f1>>a>>b;
        probablity *= ((a - 1) / a / (aold - 1));
        ans += probablity * bold;
        aold = a;
        bold = b;
    }
    probablity /= (aold - 1);
    f2<<fixed<<setprecision(15)<<n - (ans + probablity * bold);
    f1.close();
    f2.close();
}
