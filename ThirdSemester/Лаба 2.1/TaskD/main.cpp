#include <bits/stdc++.h>

using namespace std;

int n;
vector < vector < int > > g;
vector <int> ans;
vector <int> path;
vector <bool> was;
vector <int> cycle;
vector <int> index;

void findPath () {
    path.clear();
    path.push_back(0);
    //was[0] = true;
    std::shuffle(index.begin() + 1, index.end(), std::mt19937(std::random_device()()));
    for (int k = 0; k < n - 1; k++){
        int i = index[k];
        //if (was[i]) continue;
        //was[i] = 1;
        int maxi = -2;
        for (int j = 0; j < path.size(); j++){
            if (!g[path[j]][i]) {
                maxi = j - 1;
                break;
            }
        }
        if (maxi == -2){
            maxi = path.size() - 1;
        }
        //u-..umaxi->ui->umaxi+1...upath.size()-1
        vector <int> kek;
        for (int j = 0; j <= maxi; j++){
            kek.push_back(path[j]);
        }
        kek.push_back(i);
        for (int j = maxi + 1; j < path.size(); j++){
            kek.push_back(path[j]);
        }
        path.resize(0);
        for (int j = 0; j < kek.size(); j++){
            path.push_back(kek[j]);
        }
    }
}

int main()
{
    ifstream f1("guyaury.in");
    ofstream f2("guyaury.out");
    f1>>n;
    was.resize(n, false);
    string s;
    getline(f1, s);
    g.resize(n, vector <int> (n, 0));
    for (int i = 1; i <= n; i++){
        ans.push_back(i - 1);
        getline(f1, s);
        for (int j = 1; j < i; j++){
            char now = s[j - 1];
            g[i - 1][j - 1] = (now - '0');
            g[j - 1][i - 1] = (g[i - 1][j - 1] == 1) ? 0 : 1;
        }
    }
    for (int i = 1; i < n; i++){
        index.push_back(i);
    }
    /*for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout<<g[i][j]<<' ';
        }
        cout<<endl;
    }*/
    findPath();
    while (!g[path[path.size() - 1]][path[0]]){
        findPath();
    }
    for (int i = 0; i < path.size(); i++){
        f2<<path[i] + 1<<' ';
    }
}
