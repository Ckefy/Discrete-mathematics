#include <bits/stdc++.h>

using namespace std;

long long frac (long long c){
    long long ans = 1;
    for (int i = 1; i <= c; i++){
        ans *= i;
    }
    return ans;
}

int main()
{
    ifstream f1("num2perm.in");
    ofstream f2("num2perm.out");
    long long n, k;
    f1>>n>>k;
    vector <bool> was(n, false);
    vector <int> answer (n);
    for (long long i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (!was[j]){
                long long how = frac (n - i - 1);
                if (k >= how){
                    k -= how;
                } else {
                    answer[i] = j + 1;
                    was[j] = true;
                    break;
                }
            }
        }
    }
    for (int i = 0; i< n; i++){
        f2<<answer[i]<<' ';
    }
    f1.close();
    f2.close();
}
