#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    ifstream f1 ("nextbrackets.in");
    ofstream f2 ("nextbrackets.out");
    f1>>s;
    int n = s.length();
    int balance = 0;
    for (int i = n - 1; i >=0; i--){
        if (s[i] == ')'){
            balance++;
        } else {
            balance--;
            if (balance > 0){
                string ans = s;
                for (int j = 0; j < i; j++){
                    ans[j] = s[j];
                }
                ans[i] = ')';
                for (int j = i + 1; j < i + 1 + (n - i - balance)/2; j++){
                    ans [j] = '(';
                }
                for (int j = i + 1 + (n - i - balance)/2; j < n; j++){
                    ans[j] = ')';
                }
                f2<<ans;
                return 0;
            } else if (i == 0){
                f2<<'-';
                return 0;
            }
        }
    }
}
