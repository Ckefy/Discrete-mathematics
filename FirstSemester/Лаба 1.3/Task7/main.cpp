#include <bits/stdc++.h>

using namespace std;

int n, k;

vector <string> answer;

bool check (int smth, string ans){
    for (int i = 0; i < ans.length(); i++){
        if (ans[i] == char (smth + int ('0'))){
            return false;
        }
    }
    return true;
}

void gen (int dep, int start, string ans){
    if (dep == n){
        answer.push_back(ans);
        return;
    }
    for (int i = 1; i <= n; i++){
        if (!check (i, ans)) continue;
        int z = i;
        string s = "";
        while (z != 0){
            s = char (z%10 + int ('0')) + s;
            z/=10;
        }
        if (ans.length() == 0){
            gen (dep + 1, i + 1, ans + s);
        } else {
            gen (dep + 1, i + 1, ans + ' '+ s);
        }
    }
}

int main()
{
    ifstream f1("permutations.in");
    ofstream f2("permutations.out");
    f1>>n;
    //cin>>n;
    gen(0, 1, "");
    for (int i = 0; i < answer.size(); i++){
        f2<<answer[i]<<endl;
    }
    f1.close();
    f2.close();
}
