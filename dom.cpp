#include <bits/stdc++.h>

using namespace std;

long long m, ans;
long long F[88];
long long nums[4] = {11, 5, 3, 2};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m;
    if (m == 1) cout << 1;
    else {
        ans = -1;

        F[0] = 1;
        F[1] = 1;
        for (int i = 2; i < 88; i++) { F[i] = F[i-1] + F[i-2];}

        for (int i = 87; i > 3; i--) {
            if (i == 11 || i == 5) continue;
            while (m % F[i] == 0) { 
                m /= F[i]; 
                ans += i + 1;
            }
        }

        if (m > 1) {    
            for (int i = 0; i < 4; i++) {
                while (m % F[nums[i]] == 0) { 
                    m /= F[nums[i]]; 
                    ans += nums[i] + 1;
                }
            }
        }

        if (m == 1) cout << ans;
        else cout << "NIE";
    }

    return 0;
}