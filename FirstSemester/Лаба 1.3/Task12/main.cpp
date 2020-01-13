#include <bits/stdc++.h>

using namespace std;

vector < vector < string > > a(11);

void get (int pos, int num, string s){ //pos - where is common, num - which we add, s - we copy
    string ans = "";
    for (int i = 0; i < pos; i++){
        ans += s[i];
    }
    //case of 10 number add!!!!!!!!!!
    if (num != 10){
            ans += char (int ('0') + num);
    } else {
        ans += "A";
    }
    for (int i = pos; i < s.length(); i++){
        ans += s[i];
    }
    a[num].push_back(ans);
}

int main()
{
    int n, m;
    ifstream f1("part2sets.in");
    ofstream f2("part2sets.out");
    f1>>n>>m;
    string s = "1";
    a[1].push_back(s);
    for (int i = 2; i <= 10; i++){
        for (int j = 0; j < a[i - 1].size(); j++){
            string s = a[i - 1][j];
            for (int k = 0; k < s.length(); k++){
                if (s[k] == ','){
                    get (k, i, s);
                } else if (k == s.length() - 1){
                    string ans = s;
                    if (i != 10){
                        ans += ','; //case of 10 number add!!!!!!!!!!
                        ans += char (int ('0') + i); //добавление после последнего
                        a[i].push_back(ans);
                        ans = s;
                        ans += char (int ('0') + i); //добавление к последнему
                        a[i].push_back(ans);
                    } else {
                        ans += ','; //case of 10 number add!!!!!!!!!!
                        ans += "A"; //добавление после последнего
                        a[i].push_back(ans);
                        ans = s;
                        ans += "A"; //добавление к последнему
                        a[i].push_back(ans);
                    }
                }
            }
        }
    }
    for (int i = 0; i < a[n].size(); i++){
        string s = a[n][i];
        int count = 0;
        for (int j = 0; j < s.length(); j++){
            if (s[j] == ','){
                count++;
            }
        }
        if (count != m - 1){
            continue;
        }
        for (int j = 0; j < s.length(); j++){
            if (s[j] == ','){
                f2<<endl;
            } else {
                if (s[j] == 'A'){
                    f2<<10<<' ';
                } else {
                    f2<<s[j]<<' ';
                }
            }
        }
        f2<<endl<<endl;
    }
    f1.close();
    f2.close();
}
