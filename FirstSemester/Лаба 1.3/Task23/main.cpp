#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    string prev, next;
    ifstream f1 ("nextvector.in");
    ofstream f2 ("nextvector.out");
    f1>>s;
    prev = s, next = s;
    int n = s.length();
    for (int i = n - 1; i >=0; i--){
        if (s[i] == '1' && i == n -1){
             prev[i] = '0';
             break;
        } else if (s[i] == '1'){
            prev[i] = '0';
            prev[i + 1] = '1';
            break;
        } else {
            prev[i] = '1';
        }
        if (s[i] == '0' && i == 0){
            prev = "-";
        }
    }
    int now = n - 1;
    if (s[now] == '0'){
        next[now] = '1';
    } else{
        while (s[now] == '1'){
            next[now] = '0';
            now--;
            if (now < 0){
                next = "-";
                break;
            }
        }
        if (next != "-"){
                next[now] = '1';
        }
    }
    f2<<prev<<endl<<next<<endl;
    f1.close();
    f2.close();
}
