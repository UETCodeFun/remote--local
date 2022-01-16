#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define getbit(n,i) ((n>>(i-1))&1)
#define offbit(n,i) (n^(1<<(i-1)))
#define onbit(n,i) (n|(1<<(i-1)))
#define cntone(x) (__builtin_popcount(x))
using namespace std;
ll n, sum = 0, k, a[20];
pair <ll, int> f[(1<<16)+10][20];
vector<int> cn0,cn1;
int main()
{
    //freopen("h.inp", "r", stdin);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % k != 0) {
        cout << "no";
        return 0;
    }
    sum = sum / k;
    for (int i = 1; i <= n; i++)
        if (a[i] > sum) {
            cout << "no";
            return 0;
        }
    for (int tt = 1; tt <= (1<<n); tt++)
        for (int i = 1; i <= n; i++)
            f[tt][i] = {1e9, 1e9};
    for (int i = 1; i <= n; i++) {
        f[(1<<(i-1))][i].fi = a[i];
        f[(1<<(i-1))][i].se = 1;
    }
    for (int tt = 1; tt <= (1<<n); tt++) {
        cn0.clear();
        cn1.clear();
        for (int bit = 1; bit <= n; bit++) {
            if (getbit(tt, bit) == 1)
                cn1.push_back(bit);
            else
                cn0.push_back(bit);
        }
        for (int i = 0; i < cn1.size(); i++) {
            int _1 = cn1[i];
            for (int j = 0; j < cn0.size(); j++) {
                int _0 = cn0[j];
                int ttm = onbit(tt, _0);
                if (f[tt][_1].fi + a[_0] <= sum) {
                    f[ttm][_0].fi = f[tt][_1].fi + a[_0];
                    f[ttm][_0].se = f[tt][_1].se;
                }
                else {
                    if (f[tt][_1].fi == sum) {
                        f[ttm][_0].fi = a[_0];
                        f[ttm][_0].se = f[tt][_1].se + 1;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (f[(1<<n)-1][i].fi == sum && f[(1<<n)-1][i].se == k) {
            cout << "yes";
            return 0;
        }
    }
    cout << "no";
}
 
