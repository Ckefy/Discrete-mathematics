#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream f1("num2part.in");
    ofstream f2("num2part.out");
    int n, k;
    f1>>n>>k;
    vector < vector < long long > > dp(n + 1, vector <long long> (n+1));
   for (int i = 0; i <= n; i++){
        dp[i][i] = 1;
    }
    for (int i = 0; i <= n; i++){
        for (int j = n - 1; j >= 0; j--){
            if (j > i){
                dp[i][j] = 0;
            } else {
                if (j<i) {
                        if (j + 1 <= n && (i-j>=0)) dp[i][j] = dp[i][j + 1] + dp[i - j][j];;
                }
            }
        }
    }
    int last = 1;
    vector <int> ans;
    //Берем от ласта до now, если меньше, то -=, иначе берем его и идем дальше
    int have = 1;
    while (n > 0) {
        while (have < n && dp[n][have] - dp[n][have + 1] <= k) {
            k -= dp[n][have] - dp[n][have + 1];
            have++;
        }
        ans.push_back(have);
        n -= have;
    }

    for (int i = 0; i < ans.size() - 1; i++){
        f2<<ans[i]<<'+';
    }
    f2<<ans[ans.size() - 1];
}
