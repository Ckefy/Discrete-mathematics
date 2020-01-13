#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n, m, upperColor = 0, inf = 1000000;

class Tuple{

public:
    ll first, second, color;

    Tuple (ll first, ll second, ll color): first(first), second(second), color(color){}
};

vector <Tuple> edges;
vector <bool> I;

class DSU {

public:
    vector <ll> master;
    vector <ll> rank;

    DSU(){
        for (int i = 0; i < n; i++){
            master.push_back(i);
            rank.push_back(1);
        }
    }

    ll findMaster(ll now){
        if (now == master[now]){
            return now;
        } else {
            master[now] = findMaster(master[now]);
            return master[now];
        }
    }

    void connect (ll from, ll to){
        ll masterFrom = findMaster(from);
        ll masterTo = findMaster(to);
        if (rank[masterTo] < rank[masterFrom]) {
                master[masterTo] = masterFrom;
        } else {
            master[masterFrom] = masterTo;
        }
        if (rank[masterFrom] == rank[masterTo]) {
            rank[masterTo] = rank[masterTo] + 1;
        }
    }
};

vector < vector < ll > > matrix;
vector <ll> X1;
vector <ll> X2;
vector <ll> dist;
vector <ll> path;

ll BFS(){
    dist.resize(0);
    dist.resize(m, inf);
    ll mini = -1, minv = inf;
    queue <ll> que;
    for (ll i : X1){
        que.push(i);
        dist[i] = 0;
    }
    while (!que.empty()){
        ll temp = que.front();
        que.pop();
        for (ll i : matrix[temp]){
            if (dist[i] > 1 + dist[temp]){
                que.push(i);
                dist[i] = 1 + dist[temp];
                path[i] = temp;
            }
        }
    }
    for (ll i : X2){
        if (dist[i] < minv){
            minv = dist[i];
            mini = i;
        }
    }
    return mini;
}

int main()
{
   ifstream f1("rainbow.in");
   ofstream f2("rainbow.out");
   f1>>n>>m;
   for (int i = 0; i < m; i++){
        ll temp1, temp2, temp3;
        f1>>temp1>>temp2>>temp3;
        temp1--; temp2--; temp3--;
        Tuple tupl = Tuple(temp1, temp2, temp3);
        edges.push_back(tupl);
        upperColor = max(upperColor, tupl.color + 1);
   }
    I.resize(m, false);
   while (true){
        matrix.resize(0);
        matrix.resize(m);
        path.resize(0);
        path.resize(m, -1);
        vector <bool> colors (upperColor, false);
        for (int i = 0; i < m; i++){
            if (I[i]){
                DSU dsu = DSU();
                colors.resize(0);
                colors.resize(upperColor, false);
                for (int j = 0; j < m; j++){
                    if (i == j){
                        continue;
                    }
                    if (I[j]){
                        dsu.connect(edges[j].first, edges[j].second);
                        colors[edges[j].color] = true;
                    }
                }
                for (int j = 0; j < m; j++){
                    if (!I[j]){
                        if (dsu.findMaster(edges[j].first) != dsu.findMaster(edges[j].second)){
                            matrix[i].push_back(j);
                        }
                        if (!colors[edges[j].color]){
                            matrix[j].push_back(i);
                        }
                    }
                }
            }
        }
        X1.resize(0);
        X2.resize(0);
        colors.resize(0);
        colors.resize(upperColor, false);
        DSU newDsu = DSU();
        for (int i = 0; i < m; i++){
            if (I[i]){
                newDsu.connect(edges[i].first, edges[i].second);
                colors[edges[i].color] = true;
            }
        }
        for (int j = 0; j < m; j++){
            if (!I[j]){
                if (newDsu.findMaster(edges[j].first) != newDsu.findMaster(edges[j].second)){
                    X1.push_back(j);
                }
                if (!colors[edges[j].color]){
                    X2.push_back(j);
                }
            }
        }
        ll current = BFS();
        if (current == -1){
            break;
        }
        while (current != -1){
            I[current] = !I[current];
            current = path[current];
        }
   }
   vector <ll> answer;
   for (int i = 0; i < m; i++){
        if (I[i]){
            answer.push_back(i);
        }
   }
   f2<<answer.size()<<endl;
   for (ll i : answer){
        f2<<i + 1<<' ';
   }
   f1.close();
   f2.close();
}
