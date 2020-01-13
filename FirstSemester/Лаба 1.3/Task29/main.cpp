#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    ifstream f1 ("nextpartition.in");
    ofstream f2 ("nextpartition.out");
    f1>>s;
    int count = 0;
    int start;
    for (int i = 0; i < s.length(); i++){
        if (s[i] != '='){
            count = count * 10 + int(s[i]) - int ('0');
        }
        else {
            start = i + 1;
            break;
        }
    }
    int n = count;
    count = 0;
    vector <int> a;
    for (int i = start; i < s.length(); i++){
        if (s[i] != '+'){
           count = count * 10 + int(s[i]) - int ('0');
        } else {
            a.push_back(count);
            count = 0;
        }
    }
    a.push_back(count);
    if (n == a[0]){
        f2<<"No solution"<<endl;
        return 0;
    }
    int last = a.size() - 1, prelast = a.size() - 2;
    a[last]--;
    a[prelast]++;
    if (a[prelast] > a[last]){
        a[prelast] += a[last];
        a[last] = -1;
    } else {
        while (a[prelast] *2 <= a[last]){
            a.push_back(a[last] - a[prelast]);
            a[last] = a[prelast];
            last++;
            prelast++;
        }
    }
    f2<<n<<'=';
    for (int i = 0; i < a.size(); i++){
        if (a[i] == -1){
            continue;
        }
        else if (i !=0){
                f2<<'+'<<a[i];
        } else {
            f2<<a[i];
        }
    }
    f1.close();
    f2.close();
}
