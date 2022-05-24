#include <bits/stdc++.h>

using namespace std;

constexpr int max_n =  1e5 + 7;
constexpr int mod = 1e9 + 7;

int n;
int Z[max_n]; 
bool A[max_n];
int B[max_n];
int na_pewno[max_n];
bool rozpatrzone[max_n];

long long k, m, ans;
bool oke;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    ans = 1;
    m = 0;
    k = 0;
    oke = true;

    A[0] = true;
    cin >> n;
    for (int i = 1; i <= n; i++) { 
        cin >> Z[i];
        if (i > 2 && B[Z[i]] == 1 && Z[i] != Z[i-2]) oke = false;
        if (i > 1 && B[Z[i]] == 1 && Z[i] == Z[i-1]) oke = false;
        B[Z[i]]++;
        if (B[Z[i]] > 2) oke = false;
    }
    
    if (!oke) { cout << 0; return 0; }

    if (n == 3 && Z[1] != Z[3]) { cout << 0; return 0; }

    na_pewno[2] = Z[1];
    na_pewno[n-1] = Z[n];

    rozpatrzone[1] = true;
    A[Z[1]] = true;
    if (n > 2 && Z[1] == Z[3]) { rozpatrzone[3] = true; }
    rozpatrzone[n] = true;
    A[Z[n]] = true;
    if (n > 2 && Z[n] == Z[n-2]) { rozpatrzone[n-2] = true; }

    for(int i = 2; i <= n-2; i++) {
        if(!rozpatrzone[i] && Z[i] == Z[i+2]) {
            if (A[Z[i]]) { cout << 0; return 0; } 
            A[Z[i]] = true;
            na_pewno[i+1] = Z[i];
            rozpatrzone[i] = rozpatrzone[i+2] = true;
        }
    }

    for (int i = 2; i <= n-1; i++) {
        if (!rozpatrzone[i] && na_pewno[i-1]) {
            if(na_pewno[i+1] && na_pewno[i+1] != Z[i]) { cout << 0; return 0; } 
            na_pewno[i+1] = Z[i];
            rozpatrzone[i] = true;
            if (A[Z[i]]) { cout << 0; return 0; } 
            A[Z[i]] = true;
        }
        else if (!rozpatrzone[i] && na_pewno[i+1]) {
            if(na_pewno[i-1] && na_pewno[i-1] != Z[i]) { cout << 0; return 0; } 
            na_pewno[i-1] = Z[i];
            rozpatrzone[i] = true;
            if (A[Z[i]]) { cout << 0; return 0; }
            A[Z[i]] = true;
        }
    }

    for (int i = n-1; i >= 2; i--) {
        if (!rozpatrzone[i] && na_pewno[i-1]) {
            if(na_pewno[i+1] && na_pewno[i+1] != Z[i]) { cout << 0; return 0; } 
            na_pewno[i+1] = Z[i];
            rozpatrzone[i] = true;
            if (A[Z[i]]) { cout << 0; return 0; } 
            A[Z[i]] = true;
        }
        else if (!rozpatrzone[i] && na_pewno[i+1]) {
            if(na_pewno[i-1] && na_pewno[i-1] != Z[i]) { cout << 0; return 0; } 
            na_pewno[i-1] = Z[i];
            rozpatrzone[i] = true;
            if (A[Z[i]]) { cout << 0; return 0; }
            A[Z[i]] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!B[i]) k++;
    }

    int j = 1;
    for (int i = 1; i < n; i++) {
        if(!na_pewno[i]) { 
            m += k; 
            m %= mod;
            na_pewno[i] = 1;
            j = i;
            while(j < n-1 && !rozpatrzone[j+1]) {
                j += 2;
                m += k;
                m %= mod; 
                na_pewno[j] = 1;
            }
            k--;
            ans *= m;
            ans %= mod;
            m = 0;

        }
    }

    cout << ans;

    return 0;
}