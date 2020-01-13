#include <bits/stdc++.h>

using namespace std;

long long frac (long long up, long long down1, long long down2){
    long long ans = 1;
    long long a = down1;
    down1 = max (down1, down2);
    if (a != down1){
        down2 = a;
    }
    for (int i = down1 + 1; i <= up ; i++){
        ans*=i;
    }
    for (int i = 1; i <= down2; i++){
        ans/=i;
    }
    return ans;
}

int main()
{
    ifstream f1("num2choose.in");
    ofstream f2("num2choose.out");
    long long n, k, m;
    f1>>n>>k>>m;
    int next = 1;
    vector <long long> answer;
    while (k > 0){
        long long c = frac((n-1), (k-1), (n - k));
        if (m < c){
            answer.push_back(next);
            k--;
        } else {
            m -= c;
        }
        n--;
        next++;
    }
    for (int i = 0; i< answer.size(); i++){
         f2<<answer[i]<<' ';
    }
    f1.close();
    f2.close();
}
