// Magdalena Dolesniak

#include <bits/stdc++.h>

using namespace std;

constexpr int max_n = 5*1e5 + 7;
constexpr int max_val = 1e9 + 5;

int n, t, d, j, current_s, current_e, current_idx, prev_s, last_e;
bool oke;
int upd_s, upd_t, upd_idx;
int s, e, idx; 
int visited[max_n];
int T[max_n];
int E_non_sorted[max_n];
tuple<int, int, int> S[max_n];
pair<int, int> E[max_n];

vector<pair<int, int>> ans;
vector<pair<int, int>> ans2;
priority_queue<pair<int, int>> upd;

void push_upd_e() {
    
    int k = last_e;
    while (k >= 0 && visited[E[k].second] == 2) k--;
    if (k < 0) return;
    int e1, e2;
    if(!upd.empty()) e1 = prev_s - 1;
    else e1 = E[k].first;

    while (e1 > current_e) { 
        while (k >= 0 && E[k].first == e1) { 
            if (visited[E[k].second]) { k--; continue; }
            visited[E[k].second] = 1;
            upd.push({-T[E[k].second], E[k].second});
            k--;
        }

        while (k >= 0 && visited[E[k].second] == 2) k--;
        if (k < 0) break; 
        e2 = E[k].first; 
        upd_t = upd.top().first + (min(e1, prev_s - 1) - e2); 
        upd_idx = upd.top().second;
        upd.pop();
        upd.push({upd_t, upd_idx});  

        e1 = e2; 
    }

    while (k >= 0 && E[k].first >= current_s) {
        if (visited[E[k].second])  { k--; continue; }
        visited[E[k].second] = 1;
        upd.push({-T[E[k].second], E[k].second});

        k--;
    }

    last_e = k; // last non visited
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    oke = false;

    cin >> n;

    for (int i = 0; i < n; i++) { 
        cin >> t >> d;
        if (d - t < 0) visited[i] = 2;
        else oke = true;

        S[i] = {d - t + 1, d, i}; 
        E[i] = {d, i};
        T[i] = t;
        E_non_sorted[i] = d;
    }

    if (!oke) { cout << 0; return 0; }

    sort(E, E + n);
    sort(S, S + n);

    j = n - 1;
    last_e = n - 1;
    current_s = E[n-1].first + 2;


    while (j >= 0) {

        tie(s, e, idx) = S[j];
        if (visited[idx]) { j--; continue; }

        prev_s = current_s;
        if(upd.empty()) { 

            current_s = s;
            current_e = e;
            current_idx = idx;
            visited[idx] = 1; 
            ans.push_back({e, idx}); 
            
            j--;
            push_upd_e(); 

            continue;

        }

        upd_s = current_s + upd.top().first;
        if (upd_s < 1 || s > upd_s) { 
            current_s = s; 
            current_e = e;
            current_idx = idx;
            visited[idx] = 1; 
            ans.push_back({e, idx}); 
            
            j--; 

        }
        else {
            current_s = upd_s;
            current_idx = upd.top().second;
            current_e = E_non_sorted[current_idx];
            ans.push_back({current_e, current_idx}); 
            upd.pop(); 

        }

        push_upd_e(); 

    }

    prev_s = current_s;

    while (!upd.empty()) {
        upd_s = current_s + upd.top().first;
        if (upd_s < 1) break;
        current_s = upd_s; 
        
        current_idx = upd.top().second;
        ans.push_back({E_non_sorted[current_idx], current_idx});
        upd.pop(); 
    }

    sort(ans.rbegin(), ans.rend());
    prev_s = E[n-1].first + 2;
    for (auto x : ans) {
        ans2.push_back({x.second + 1, min(prev_s, x.first) - T[x.second] + 1});
        prev_s = min(prev_s, x.first) - T[x.second];
    }

    reverse(ans2.begin(), ans2.end());

    cout << ans2.size() << '\n';
    
    
    for (auto v : ans2) {
        cout << v.first << ' ' << v.second << '\n';
    }
    
    

    return 0;
}