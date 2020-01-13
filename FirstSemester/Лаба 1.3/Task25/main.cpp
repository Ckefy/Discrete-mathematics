#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    ifstream f1 ("nextchoose.in");
    ofstream f2 ("nextchoose.out");
    f1>>n>>k;
    vector <int> mas (k);
    vector <bool> was (n + 1, false);
    for (int i = 0; i < k; i++){
        f1>>mas[i];
        was[mas[i]] = true;
    }
    int nowmax = n;
    int start;
    for (int i = k - 1; i >= 0; i--){
        if (mas[i] == nowmax){
            nowmax--;
            if (i == 0){
                f2<<-1<<endl;
                return 0;
            }
            continue;
        } else {
            start = i;
            break;
        }
    }
    int now = mas[start] + 1;
    for (int i = start; i < k; i++){
        mas[i] = now;
        now++;
    }
    for (int i = 0; i < k; i++){
        f2<<mas[i]<<' ';
    }
}
