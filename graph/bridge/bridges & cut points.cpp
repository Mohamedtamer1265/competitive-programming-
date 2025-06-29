#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define no cout << "No" << endl
#define el endl
#define fr first
#define sc second
#define all(x) begin(x), end(x)
#define yes cout << "Yes" << endl
const unsigned int N = 1e5 + 2, M = 502, mod = 998244353;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key
vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

void MO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

// 55 aktb kod 3dl y7tar 3dwk fik

void solve() {
    // back edge means visited node that was visited before and it's not parent
    // back edge is between me and another ancestor (same subtree
    // bridge is an edge if you removed it the graph will be 2 components (break)
    // bridge cannot be a back_edge
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].pb({v, i});
        g[v].pb({u, i});
    }

    vector<int> vis(n), low(n, 1e9), dep(n), is_bridge(m);
    function<void(int, int)> dfs = [&](int v, int p) {
        vis[v] = 1;
        int kids = 0;
        for (auto [u, e]: g[v]) {
            if (u == p)continue;
            if (vis[u]) // back edge
            {
                low[v] = min(low[v], dep[u]);
                continue;
            }
            kids++;
            dep[u] = 1 + dep[v];
            dfs(u, v); // dfs first to be sure all subtrees are handled correctly
            low[v] = min(low[v], low[u]);

            // this is a tree edge
            // so we need to check if it is bridge or not
            // edge v -- > u
            if (low[u] > dep[v])  // bridge
                is_bridge[e] = 1;

            // articulation point
            // when you remove it with all edges it will be a cut point
            if (low[u] >= dep[v])
                if (p != -1 || kids > 1);// cut point
            // Edge case: if the starting node of the DFS (root) has only one child,
            // it might be mistakenly considered an articulation point, but it's not.

        }
        if (p == -1 && kids > 1); // root is a cut point
    };
    dfs(0,-1);
    vector<int> id_tr(n, -1);
    int id = 0;
    function<void(int)> dfs_tree = [&](int v) {
        id_tr[v] = id;
        for (auto [u, e]: g[v]) {
            if (is_bridge[e] || id_tr[u] != -1)continue;
            dfs_tree(u);
        }
    };
    for (int i = 0; i < n; i++) {
        if (id_tr[i] != -1)continue;
        dfs_tree(i);
        id++;
    }
    vector<vector<int>> tree(n);
    for (int v = 0; v < n; v++) {
        for (auto [u, e]: g[v]) {
            if (id_tr[u] != id_tr[v])
                tree[id_tr[v]].pb(id_tr[u]);
        }
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

