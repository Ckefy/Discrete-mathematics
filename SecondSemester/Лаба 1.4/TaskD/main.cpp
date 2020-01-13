#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector < vector < double > > a, b;

int main()
{
    ifstream f1 ("markchain.in");
    ofstream f2 ("markchain.out");
    int n;
    cin>>n;
    double e = 1e-5;
    a.resize(n, vector <double> (n));
    b.resize(n, vector <double> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin>>a[i][j];
            b[i][j] = a[i][j];
        }
    }
    ll counter = 0;
    ll n2 = n * n;
    while (counter != n2){
        counter = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                double sum = 0;
                for (int k = 0; k < n; k++){
                    sum += a[i][k] * a[k][j];
                }
                b[i][j] = sum;
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j ++){
                if (abs(a[i][j] - b[i][j]) <= e){
                    counter++;
                }
                a[i][j] = b[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout<<fixed<<setprecision(15)<<a[0][i]<<'\n';
    }
    f1.close();
    f2.close();
}
