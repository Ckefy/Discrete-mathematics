#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ifstream f1 ("brackets2num2.in");
    ofstream f2 ("brackets2num2.out");
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
    vector <char> stack;
    for (int i = 0; i < 2 * n; i++){
        if (s[i] == '('){
                dep++;
                stack.push_back('(');
        } else if (s[i] == ')'){
            if (dep + 1 >= 0){
                k += (d[2 *  n - i - 1][dep + 1] * int (pow (2, (2 * n - i - 1 - dep - 1)/2)));
            }
            stack.pop_back();
            dep--;
        } else if (s[i] == '[') {
            if (dep + 1 >= 0){
                k += (d[2 *  n - i - 1][dep + 1] * int (pow (2, (2 * n - i - 1 - dep - 1)/2)));
            }
            if (stack.size() != 0 && stack[stack.size() - 1] == '(')
                if (dep - 1 >= 0){
                    k += (d[2 *  n - i - 1][dep - 1] * int (pow (2, (2 * n - i - 1 - dep + 1)/2)));
                }
            dep++;
            stack.push_back('[');
        } else {
            if (dep + 1 >= 0){
                k += (d[2 *  n - i - 1][dep + 1] * int (pow (2, (2 * n - i - 1 - dep - 1)/2)));
            }
            if (stack.size() != 0 && stack[stack.size() - 1] == '(')
                if (dep - 1 >= 0){
                    k += (d[2 *  n - i - 1][dep - 1] * int (pow (2, (2 * n - i - 1 - dep + 1)/2)));
                }
            if (dep + 1 >= 0){
                k += (d[2 * n - i - 1][dep + 1] * int (pow (2, (2 * n - i - 1 - dep - 1)/2)));
            }
            dep--;
            stack.pop_back();
        }
    }
    f2<<k<<endl;
    f1.close();
    f2.close();
}
