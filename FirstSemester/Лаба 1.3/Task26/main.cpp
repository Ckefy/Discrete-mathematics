#include <bits/stdc++.h>

using namespace std;

vector <int> was;

int check (int need){
    int ans = -1;
    int mini = 1000000;
    for (int i = 0; i < was.size(); i++){
        if (was[i] == -1){
            continue;
        }
        if (was[i] < mini && was[i] > need){
            mini = was[i];
            ans = i;
        }
    }
    return ans;
}

int main()
{
    int n, k;
    ifstream f1("nextsetpartition.in");
    ofstream f2("nextsetpartition.out");
    while (f1>>n>>k){
        if (n == 0 && k == 0){
            return 0;
        }
        was.resize(0);
        vector < vector < int > > mas (k, vector <int> ());
        for (int i = -1; i < k; i++){
            string s;
            getline(f1, s);
            if (i == -1) continue;
            int count = 0;
            for (int j = 0; j < s.length(); j++){
                if (s[j] == ' '){
                    mas[i].push_back(count);
                    count = 0;
                } else {
                    count = count * 10 + int (s[j]) - int ('0');
                }
            }
            mas[i].push_back(count);
        }
        bool flag = true;
        for (int i = k - 1; i >=0; i--){
            int ind1 = check (mas[i][mas[i].size() - 1]);
            if (was.size() != 0 && ind1 != -1){
                mas[i].push_back(was[ind1]);
                was[ind1] = -1;
                break;
            }
            for (int j = mas[i].size() - 1; j >= 0; j--){
                int ind = check (mas[i] [j]);
                if (was.size() != 0 && j != 0 && ind != -1){
                    was.push_back(mas[i][j]);
                    mas[i][j] =  was[ind];
                    was[ind] = -1;
                    flag = false;
                    break;
                } else {
                   was.push_back(mas[i][j]);
                   mas[i][j] = - 1;
                }
            }
            if (!flag){
                break;
            }
            was.push_back(mas[i][0]);
            //cout<<mas[i][j];
            mas[i][0] = - 1;
        }
        sort (was.begin(), was.end());
        int k1 = 0;
        for (int i = 0; i < k; i++){
            int count1 = 0;
            for (int j = 0; j < mas[i].size(); j++){
                if (mas[i][j] == -1){
                    continue;
                }
                count1++;
            }
            if (count1 != 0){
                k1++;
            }
        }
        for (int i = 0; i < was.size(); i++){
            if (was[i] == -1){
                continue;
            }
            k1++;
        }
        f2<<n<<' '<<k1<<endl;
        for (int i = 0; i < k; i++){
            int count1 = 0;
            for (int j = 0; j < mas[i].size(); j++){
                if (mas[i][j] == -1){
                    continue;
                }
                count1++;
                f2<<mas[i][j]<<' ';
            }
            if (count1 !=0){
                f2<<endl;
            }
        }
        for (int i = 0; i < was.size(); i++){
            if (was[i] == -1){
                continue;
            }
            f2<<was[i]<<endl;
        }
        f2<<endl;
    }
}
