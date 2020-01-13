#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    ifstream f1 ("nextmultiperm.in");
    ofstream f2 ("nextmultiperm.out");
    cin>>n;
    vector <int> a (n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    if (n == 1){
        cout<<0;
        return 0;
    }
    int start;
    for (int i = n - 1; i > 0; i--){
        if (a[i] <= a[i - 1]){
            if (i == 1){
                for (int j = 0; j < n; j++){
                    cout<<0<<' ';
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
        cout<<a[i]<<' ';
    }
}
