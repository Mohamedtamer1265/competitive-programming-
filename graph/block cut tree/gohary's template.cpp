
vector<vector<int>> bcc;
    vector<int> vis(n), low(n, 1e9), depth(n), cut(n), stk;
    function<void(int, int)> dfs_cuts = [&](int v, int p) {
        vis[v] = 1;
        stk.push_back(v);
        int kids = 0;
        for (int u : g[v]) {
            if (u == p) continue;
            if (vis[u]) {
                low[v] = min(low[v], depth[u]);
                continue;
            }
            kids++;
            depth[u] = 1 + depth[v];
            dfs_cuts(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= depth[v]) {
                cut[v] = (p != -1 || kids > 1);
                bcc.push_back({v});
                while (bcc.back().back() != u) {
                    bcc.back().push_back(stk.back());
                    stk.pop_back();
                }
            }
        }
    };
    dfs_cuts(0, -1);
    int cur_id = 0;
    vector<int> id(n);
    for (int i = 0; i < n; i++) {
        if (cut[i]) id[i] = cur_id++;
    }
    vector<vector<int>> tree(cur_id);
    for (const auto& comp : bcc) {
        int v = cur_id++;
        tree.push_back({});
        for (int u : comp) {
            if (cut[u]) {
                tree[v].push_back(id[u]);
                tree[id[u]].push_back(v);
            } else {
                id[u] = v;
            }
        }
    }
