#include <bits/stdc++.h>

using namespace std;

int n;

vector <string> answer;

void gen (int sum, int start, string ans){
    if (sum == n){
        answer.push_back(ans);
        return;
    } else if (sum > n){
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
            gen (sum + i, i, ans + s);
        } else {
            gen (sum + i, i, ans + '+'+ s);
        }
    }
}

int main()
{
    ifstream f1("partition.in");
    ofstream f2("partition.out");
    f1>>n;
    //cin>>n;
    gen(0, 1, "");
    for (int i = 0; i < answer.size(); i++){
        f2<<answer[i]<<endl;
    }
    f1.close();
    f2.close();
}
