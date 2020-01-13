#include <bits/stdc++.h>
#define ll int

using namespace std;

int main()
{
    ifstream f1 ("shooter.in");
    ofstream f2 ("shooter.out");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    f1>>n>>m>>k;
    double p;
    double sum = 0, our;
    for (int i = 0; i < n; i++){
        f1>>p;
        sum += pow (1 - p, m);
        if (i == k - 1)
            our = pow (1 - p, m);
    }
    double ans = our / sum;
    f2<<fixed<<setprecision(14)<<ans;
    f1.close();
    f2.close();
}
