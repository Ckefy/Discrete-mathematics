#include <bits/stdc++.h>

using namespace std;

vector <string> ans;
int n;

void gen (int open, int close, string now){
    if (open + close == 2 * n){
        ans.push_back(now);
        return;
    }
    if (open < n){
        gen (open + 1, close, now + '(');
    }
    if (close < open){
        gen (open, close + 1, now + ')');
    }
}

int main()
{
    ifstream f1 ("brackets.in");
    ofstream f2 ("brackets.out");
    f1>>n;
    gen(0, 0, "");
    for (int i = 0; i < ans.size(); i++){
        f2<<ans[i]<<endl;
    }
    f1.close();
    f2.close();
}
