#include <bits/stdc++.h>

using namespace std;

int n;

vector <string> answer;

void gen (int start, string ans){
    if (start > n){
        answer.push_back(ans);
        return;
    } else if (start <= n){
        answer.push_back(ans);
    }
    for (int i = start; i <= n; i++){
        int z = i;
        string s = "";
        while (z != 0){
            s = char (z%10 + int ('0')) + s;
            z/=10;
        }
        if (ans.length() == 0){
            gen (i + 1, ans + s);
        } else {
            gen (i + 1, ans + ' '+ s);
        }
    }
}

int main()
{
    ifstream f1("subsets.in");
    ofstream f2("subsets.out");
    f1>>n;
    //cin>>n;
    gen(1, "");
    for (int i = 0; i < answer.size(); i++){
        f2<<answer[i]<<endl;
    }
    f1.close();
    f2.close();
}
