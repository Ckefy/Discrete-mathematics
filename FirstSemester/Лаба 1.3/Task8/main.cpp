#include <bits/stdc++.h>

using namespace std;

int n, k;

vector <string> answer;

void gen (int dep, int start, string ans){
    if (dep == k){
        answer.push_back(ans);
        return;
    }
    for (int i = start; i <= n; i++){
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
    ifstream f1("choose.in");
    ofstream f2("choose.out");
    f1>>n>>k;
    //cin>>n>>k;
    gen(0, 1, "");
    for (int i = 0; i < answer.size(); i++){
        f2<<answer[i]<<endl;
    }
    f1.close();
    f2.close();
}
