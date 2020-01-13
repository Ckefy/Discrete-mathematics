#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ifstream f1 ("num2brackets2.in");
    ofstream f2 ("num2brackets2.out");
    ll n, k;
    f1>>n>>k;
    k++;
    string s = "";
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
    ll dep = 0;
    vector <char> stack;
    for (int i = 0; i < 2 * n; i++){
        if (d[2 * n - i - 1][dep + 1] * (pow (2, (2 * n - i - 1 - dep - 1)/2)) >= k){
            s += '(';
            dep++;
            stack.push_back('(');
        } else {
            k -= d[2 * n - i - 1][dep + 1] * (pow (2, (2 * n - i - 1 - dep - 1)/2));
            if (!stack.empty() && stack[stack.size() - 1] == '(' && d[2 * n - i - 1][dep - 1] * (pow (2, (2 * n - i - 1 - dep + 1)/2)) >= k){
                s += ')';
                dep--;
                stack.pop_back();
            } else{
                if (!stack.empty() && stack[stack.size() - 1] == '('){
                        k -= d[2 * n - i - 1][dep - 1] * (pow (2, (2 * n - i - 1 - dep + 1)/2));
                    }
                if (d[2 * n - i - 1][dep + 1] * (pow (2, (2 * n - i - 1 - dep - 1)/2)) >= k){
                    stack.push_back('[');
                    dep++;
                    s += '[';
                } else {
                    k -= d[2 * n - i - 1][dep + 1] * (pow (2, (2 * n - i - 1 - dep - 1)/2));
                    stack.pop_back();
                    dep--;
                    s +=']';
                }
            }
        }
    }
    f2<<s<<endl;
    f1.close();
    f2.close();
}
