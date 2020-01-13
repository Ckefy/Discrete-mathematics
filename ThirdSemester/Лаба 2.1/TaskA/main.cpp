#include <bits/stdc++.h>

using namespace std;

int n;
vector < vector < int > > g;
vector <int> ans;

int findCycle(){
    int start = 0;
    int counter;
    for (int i = 0; i < n * (n - 1); i++){
        if(!g[ans[start]][ans[start + 1]]){
            counter = 2;
            while (true){
                if (g[ans[start]][ans[start + counter]] == 1 && g[ans[start + 1]][ans[start + counter + 1]] == 1) break;
                else counter++;
            }
        reverse(&ans[start + 1], &ans[start + counter + 1]);
        }
        ans.push_back(ans[start]);
        start++;
    }
    return start;
}

int main()
{
    ifstream f1("fullham.in");
    ofstream f2("fullham.out");
    f1>>n;
    string s;
    getline(f1, s);
    g.resize(n, vector <int> (n, 0));
    for (int i = 1; i <= n; i++){
        ans.push_back(i - 1);
        getline(f1, s);
        for (int j = 1; j < i; j++){
            char now = s[j - 1];
            g[i - 1][j - 1] = (now - '0');
            g[j - 1][i - 1] = (now - '0');
        }
    }
    int start = findCycle();
    for (int i = start; i < ans.size(); i++){
        f2<<ans[i] + 1<<' ';
    }
}
