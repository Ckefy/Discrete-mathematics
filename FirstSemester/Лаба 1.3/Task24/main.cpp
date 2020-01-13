#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    ifstream f1 ("nextperm.in");
    ofstream f2 ("nextperm.out");
    f1>>n;
    vector <int> b(n);
    for (int i = 0; i < n; i++){
        f1>>b[i];
    }
    vector <int> a (b);
    if (n == 1){
        f2<<0<<endl;
        f2<<0<<endl;
        return 0;
    }
    bool flag = false;
    int start;
    for (int i = n - 1; i > 0; i--){
        if (b[i] >= b[i - 1]){
            if (i == 1){
                for (int j = 0; j < n; j++){
                    f2<<0<<' ';
                }
                f2<<endl;
                flag = true;
                break;
            }
            continue;
        }
        start = i - 1;
        break;
    }
    if (!flag){
        int maxi = 0, maxind;
        for (int i = start + 1; i < n; i++){
            if (b[i] < b[start] && b[i] > maxi){
                maxi = b[i];
                maxind = i;
            }
        }
        swap (b[start], b[maxind]);
        sort (b.begin() + start + 1, b.end(), greater<int>());
        for (int i = 0; i < n; i++){
            f2<<b[i]<<' ';
        }
        f2<<endl;
    }

    /////////
    start = 0;
    for (int i = n - 1; i > 0; i--){
        if (a[i] <= a[i - 1]){
            if (i == 1){
                for (int j = 0; j < n; j++){
                    f2<<0<<' ';
                }
                return 0;
            }
            continue;
        }
        start = i - 1;
        break;
    }
    int mini = 100001, minind;
    for (int i = start + 1; i < n; i++){
        if (a[i] > a[start] && a[i] < mini){
            mini = a[i];
            minind = i;
        }
    }
    swap (a[start], a[minind]);
    sort (a.begin() + start + 1, a.end());
    for (int i = 0; i < n; i++){
        f2<<a[i]<<' ';
    }
}
