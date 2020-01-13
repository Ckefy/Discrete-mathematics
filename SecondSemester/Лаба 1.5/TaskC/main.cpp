#include <bits/stdc++.h>
#define ll int

using namespace std;

int main()
{
    ifstream f1 ("problem3.in");
    ofstream f2 ("problem3.out");
    ll mod = 1000000007;
    ll n, m, k;
    f1>>n>>m>>k;
    vector < vector < ll > > arr (n);
    vector < vector < ll > > reversed (n);
    set <ll> terminal;
    for (ll i = 0; i < k; i++){
        ll now;
        f1>>now;
        now--;
        terminal.insert(now);
    }
    vector <ll> counter (n);
    for (ll i = 0; i < m; i++){
        ll from, to;
        char symbol;
        f1>>from>>to>>symbol;
        from--;
        to--;
        arr[from].push_back(to);
        reversed[to].push_back(from);
        counter[to]++;
    }
    set <ll> fromStart, toEnd;
    queue <ll> cur;
    cur.push(0);
    while (true){
        if (cur.empty()){
            break;
        }
        ll now = cur.front();
        cur.pop();
        if (fromStart.find(now) != fromStart.end()){
                continue;
            }
            for (ll i = 0; i < arr[now].size(); i++){
                cur.push(arr[now][i]);
            }
            fromStart.insert(now);
    }
    for (set <ll>::iterator i = terminal.begin(); i != terminal.end(); i++){
        cur.push(*i);
    }
   while (true){
        if (cur.empty()){
            break;
        }
        ll now = cur.front();
        cur.pop();
        if (toEnd.find(now) != toEnd.end()){
                continue;
            }
            for (ll i = 0; i < reversed[now].size(); i++){
                cur.push(reversed[now][i]);
            }
            toEnd.insert(now);
    }
    for (ll i = 0; i < n; i++){
        if ((fromStart.find(i) == fromStart.end()) || (toEnd.find(i) == toEnd.end())){
            for (ll j = 0; j < arr[i].size(); j++){
                counter[arr[i][j]]--;
            }
            arr[i].clear();
        }
    }

    queue <ll> que;
    if (toEnd.find(0) == toEnd.end()){
        f2<<0<<endl;
        return 0;
    } else if (counter[0] != 0){
        f2<<-1<<endl;
        return 0;
    } else {
        que.push (0);
        counter[0]++;
    }
    ll dp;
    vector <ll> answer (n);
    while (true){
        if (que.empty()){
            break;
        }
        ll now = que.front();
        que.pop();
        counter[now]--;
        if (counter[now] == 0){
            dp = 0;
            for (ll i = 0; i < reversed[now].size(); i++){
                if ((fromStart.find(reversed[now][i]) != fromStart.end()) && (toEnd.find(reversed[now][i]) != toEnd.end())){
                    dp = (dp + (answer[reversed[now][i]] == 0 ? 1 : answer[reversed[now][i]])) % mod;
                }
            }
            answer[now] = dp;
            for (ll i = 0; i < arr[now].size(); i++){
                que.push(arr[now][i]);
            }
        }
    }
    for (set <ll>::iterator i = toEnd.begin(); i != toEnd.end(); i++){
        if (counter[*i] != 0){
            f2<<-1<<endl;
            return 0;
        }
    }
    answer[0] = 1;
    ll ans = 0;
    for (set <ll>::iterator i = terminal.begin(); i != terminal.end(); i++){
        ans = (ans + answer[*i]) % mod;
    }
    f2<<ans<<endl;
}
