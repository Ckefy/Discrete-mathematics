#include <bits/stdc++.h>

using namespace std;

vector <int> a;

bool compare(int a, int b){
    cout<<"1 "<<a<<" "<<b<<endl;
    cout.flush();
    string s;
    cin>>s;
    return (s == "YES");
}

void mergesort (int n)
{
    int i1, i2;
    int step=1; //какой длины сейчас массивчики
    vector <int> temp;
    while (step<n)
    {
        int left=0, mid=left+step, right=left+2*step; //левый край левого, левый край центрального и за правым краем правого
        temp.resize (0);
        while (left<n)
        {
            mid=min(mid,n); //это чтобы крч не выходило за рамки
            right=min(right,n);
            i1=left, i2=mid;
            while (i1<mid && i2<right)
                if (compare(a[i1], a[i2]))
                {
                    temp.push_back (a[i1]);
                    i1++;
                }
                else
                {
                    temp.push_back (a[i2]);
                    i2++;
                }
            while (i1<mid)
            {
                temp.push_back(a[i1]);
                i1++;
            }
            while (i2<right)
            {
                temp.push_back(a[i2]);
                i2++;
            }
            left+=2*step;
            right+=2*step;
            mid+=2*step;
        }
        for (int i=0; i<n; i++)
            a[i]=temp[i];
        step*=2;
    }
}

int main()
{
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++){
        a.push_back(i);
    }
    mergesort (n);
    cout<<0<<' ';
    for (int i=0; i<n; i++)
        cout<<a[i]<<' ';
    cout.flush();
}
