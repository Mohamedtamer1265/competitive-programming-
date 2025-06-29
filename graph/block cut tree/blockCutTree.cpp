#include <bits/stdc++.h>

#define ll long long
#define el endl
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
const int modd = 1e9 + 7;

void MO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (int i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<ll> low(n, 1e9), depth(n), vis(n), is_cut(n);
    stack<pair<int, int>> st;
    vector<vector<ll>> blocks;

    function<void(int, int)> getArt = [&](int u, int p) {
        vis[u] = 1;
        int kids = 0;
        for (auto v: adj[u]) {
            if (v == p) continue;

            if (vis[v] && depth[v] < depth[u]) // back edge
            {
                low[u] = min(low[u], depth[v]);
                st.push({u, v});
                continue;
            }

            if (!vis[v]) {
                kids++;
                depth[v] = 1 + depth[u];
                st.push({u, v});
                getArt(v, u);
                low[u] = min(low[u], low[v]);

                if (low[v] >= depth[u]) /// art
                {
                    if (p != -1 || kids > 1) {
                        is_cut[u] = 1;
                    }
                    vector<ll> block;
                    set<ll> ver;

                    while (true) {
                        auto [x, y] = st.top();
                        st.pop();
                        ver.insert(x);
                        ver.insert(y);
                        if (x == u && y == v) break;
                    }
                    for (int vertex: ver) {
                        block.pb(vertex);
                    }
                    blocks.pb(block);
                }
            }
        }

    };

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (adj[i].size())
                getArt(i, -1);
            else
                blocks.pb({i});
        }
    }
    cout << blocks.size() << el;
    for (int i = 0; i < blocks.size(); i++) {
        cout << blocks[i].size() << " ";
        for (int vertex: blocks[i]) {
            cout << vertex << " ";
        }
        cout << el;
    }
}

signed main() {
    MO();
    int t = 1;
    //  cin >> t;
    while (t--) {
        solve();
    }
}