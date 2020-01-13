#include <iostream>

using namespace std;
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream f1 ("part2num.in");
    ofstream f2 ("part2num.out");
    string s;
    f1>>s;
    vector <int> mas;
    int count = 0;
    int n = 0;
    for (int j = 0; j < s.length(); j++){
            if (s[j] == '+'){
                mas.push_back(count);
                n += count;
                count = 0;
            } else {
                count = count * 10 + int (s[j]) - int ('0');
            }
    }
    mas.push_back(count);
    n += count;
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
    int now = 1, k = 0, have = 0, last = 1;
    for (int i = 0; i < mas.size(); i++){
        int now = mas[i];
        for (int j = last; j < now; j++){
            if (n - have - j >= 0){
                    k += dp[n - have - j][j];
            }
        }
        last = now;
        have += now;
    }
    f2<<k<<endl;
}
