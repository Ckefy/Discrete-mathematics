#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector < vector < int > > g, how;
vector <int> numbers;

int dfs (int v, int depth){
    int ans = depth;
    for (int i = 0; i < g[v].size(); i++){
        if (g[g[v][i]].size()==0){
            continue;
        }
        ans = max(ans, dfs (g[v][i], depth + 1));
    }
    return ans;
}

int dfs2 (int v){
    if (g[v].size() == 0){
        return numbers[v];
    }
    int now = 0;
    int power = pow(2,g[v].size() - 1);
    for (int i = 0; i < g[v].size(); i++){
        now += power * dfs2(g[v][i]);
        power/=2;
    }
    return how[v][now];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int  n;
    cin>>n;
    g.resize(n);
    how.resize(n);
    numbers.resize(n,0);
    string answer;
    vector <int> leaves;
    for (int i = 0; i < n; i++){
        int m;
        cin>>m;
        if (m == 0){
            leaves.push_back(i);
            continue;
        }
        for (int j = 0; j < m; j++){
            int v;
            cin>>v;
            v--;
            g[i].push_back(v);
        }
        int powerm = pow (2,m);
        for (int j = 0; j < powerm; j++){
            int smth;
            cin>>smth;
            how[i].push_back(smth);
        }
    }
        cout<<dfs(n-1, 1)<<endl;
        int k = leaves.size();
        cout<<dfs2(n-1);
        int maxn = pow(2,k);
        for (int i = 1; i < maxn; i++){
            int j = k - 1;
            if (numbers[leaves[j]] == 0){
                numbers[leaves[j]] = 1;
            } else {
                while (numbers[leaves[j]] != 0){
                    numbers[leaves[j]] = 0;
                    j--;
                }
                numbers[leaves[j]] = 1;
            }
            cout<<dfs2(n-1);
        }
}
