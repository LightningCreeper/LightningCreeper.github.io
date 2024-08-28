#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int MAXN = 15;
constexpr int MAXM = 15000;
constexpr int MOD = 1e9 + 7;

ll n, k;
vector<ll> ret;

ll f[MAXN][MAXM][2];
ll a[MAXN], c[MAXM], tot;

int get(ll x) {
    return lower_bound(ret.begin(), ret.end(), x) - ret.begin();
}

bool operator<(pair<ll, ll> x, pair<ll, ll> y) {
    return c[x.first] * c[x.second] < c[y.first] * c[y.second];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;

    for (ll a2 = 1; a2 <= n; a2 *= 2)
        for (ll a3 = 1; a3 * a2 <= n; a3 *= 3)
            for (ll a5 = 1; a5 * a3 * a2 <= n; a5 *= 5)
                for (ll a7 = 1; a7 * a5 * a3 * a2 <= n; a7 *= 7)
                    ret.push_back(a7 * a5 * a3 * a2);

    sort(ret.begin(), ret.end());

    while (n) {
        a[++tot] = n % 10;
        n /= 10;
    }

    for (int i = 1; i < 10; i++)
        f[1][get(i)][i > a[1]] = 1;

    for (int i = 2; i <= tot; i++) {
        for (int j : ret) {
            for (int k = 1; k < 10; k++) {
                if (j % k != 0)
                    continue;
                if (k < a[i])
                    f[i][get(j)][0] = f[i - 1][get(j / k)][0] + f[i - 1][get(j / k)][1];
                else if (k > a[i])
                    f[i][get(j)][1] = f[i - 1][get(j / k)][0] + f[i - 1][get(j / k)][1];
                else {
                    f[i][get(j)][0] = f[i - 1][get(j / k)][0];
                    f[i][get(j)][1] = f[i - 1][get(j / k)][1];
                }
            }
        }
    }

    for (int i : ret)
        for (int j = 1; j <= tot; j++)
            c[get(i)] += f[j][get(i)][0] + (j != tot) * f[j][get(i)][1];

    for (int i : ret)
        cerr << c[get(i)] << endl;

    sort(c, c + ret.size(), greater<>());

    priority_queue<pair<ll, ll>> q;
    for (int i : ret)
        q.push(make_pair(i, ret.size() - 1));

    ll ans = 0;
    for (int i = 1; i <= k; i++) {
        auto t = q.top();
        q.pop();
        ans = (ans + c[t.first] * c[t.second]) % MOD;
        if (t.second != 1)
            q.push(make_pair(t.first, t.second - 1));
    }
    cout << ans << endl;

    return 0;
}