#include <bits/stdc++.h>

using namespace std;

constexpr int max_n = 1e6 + 7;

long long n, m;
long long k, s, x, c;
long long sum = 0;
long long r_cost = 0;

long long silnia[max_n];
long long prefix_sum[max_n];
long long base_sum = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> n >> m;

    r_cost = (n*(n-1)) % m;
    x = 1;
    
    silnia[0] = 1;
    for (int i = 1; i <= n; i++) { 
        silnia[i] = silnia[i-1]*i; 
        silnia[i] %= m;
    }

    prefix_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i-1] + i;
        prefix_sum[i] %= m;
    }

    k = 1;
    for (int i = 0; i <= n-3; i++) {
        s = (silnia[n-2-i]*k) % m;
        s *= prefix_sum[n-1] - prefix_sum[i]; 
        s %= m;
        base_sum += s; 
        base_sum %= m;
        k *= (n-1-i);
        k %= m;
    }
    sum += base_sum; 

    for (int i = 1; i <= n-1; i++) {
        base_sum += (silnia[n-1]*(n-1)) % m;
        base_sum %= m;
        sum += base_sum;
        sum %= m;
    }

    for (int i = 1; i <= n-2; i++) {
        c = x*r_cost;
        c %= m;
        sum -= c;
        sum %= m;
        
        x *= n-i;
        x %= m;
    }

    sum %= m;
    if (sum < 0) sum += m;

    cout << sum;

    return 0;
}