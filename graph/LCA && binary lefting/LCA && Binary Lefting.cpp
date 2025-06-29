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
/*
 x is ancestor if it is lay on my path

 we flat the tree according to our dfs
 so if I said u is ancestor of v, so I am sure that v is shown in my array before v
 so Tin[u] < Tin[v]
 but it's not the only condition
 we also need Tout[u] > Tout[v]

 so I can make an array and get  the sum of subtree or max min anything

 the problem shows here when you want to get something on path from x to y ()
 so path x -> y it could be x-> Lca -> y

we will get the LCA using binary lefting

 if I have x^5 = x^4 x^1  I made it as power of 2's
 so if I prepared all the powers of 2 I will use it quickly to get my ans

 up[i][u] is the 2^ith ancestor of u (stores the power of 2)
 3 ->(11) get the first ancestor after that get the second one

 how can I implement that
 if I am standing on 2^(i-1)th ancestor and I wanna go up
 so you can say the 4th ancestor is the 2nd ancestor for the 2nd ancestor
                the 8th ancestor is the 4th ancestor for the 4th ancestor
up[i][u]= up[i-1][up[i-1][u]]

get lca in n
 go over all paths of one of the nodes u and v
 and each time if the sth ancestor of u is an ancestor for v
 using Tin and Tout
 o(n) because you go over the path


 get lca in log(n)*log(n)
 you will notice that if I have node u, v if I got the Lca of node u and check if it is ancestor or not
 it will be like that 0 0 0 0 1 1 1 1  11  11 1
 0 means no this node it's not an ancestor
 if you get the first node that's ancestor for us it will work
 binary search on the kth ancestor


 get lca in log(n) using binary jumping
instead of binary search on the kth ancestor
 construct the ancestor
u,v;
 let p is the last ancestor of u and not ancestor of v
 so the we get the parent of p it will be the lca of u and v
 now we will loop on the 2^i ancestors for node u and check let it x
 if x is an ancestor of u and v so it won't contribute to the answer so the kth bit will be zero
 otherwise the kth bit will be 1

 amazing haa ?


 we can also use up vector to know the max, min , gcd anything
 mxup

 1- get the kth ancestor using up[i][u]
 2- get LCA in log(n)
 * */
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n + 1);
    const int LOG = 20;
    vector<vector<ll>> up(LOG, vector<ll>(n + 1));
/*
 make the parent of node 1 is the zero
 and the parent of the zero is the zero itself so if the answer is the zero I know that it will be -1
 * */
    for (int i = 2; i <= n; i++) {
        ll p;
        cin >> p;
        up[0][i] = p; // if we have graph we should get them using dfs
        adj[p].pb(i);
    }
    vector<int> tin(n + 1), tout(n + 1);
    int timer = 0;
    tout[0] = n; // assume there is a node 0 that's ancestor for all
    vector<ll> depth(n);
    function<void(int u, int v)> dfs = [&](int u, int p) // flat your array
    {
        tin[u] = timer++;
        for (auto& v: adj[u])
        {
            if (v == up[0][u]) continue;
            up[0][v] = u;
            depth[v] = depth[u]+1;
            dfs(v,u);
        }
        tout[u] = timer++;
    };
    dfs(1, 0);
    auto is_anc = [&](int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };
    auto lca = [&](int u, int v) -> ll {
        if (is_anc(u, v)) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (is_anc(up[i][u], v)) continue;// current anc is anc for v
            u = up[i][u];
        }
        return up[0][u]; // the parent is the lca // 2^0 of the node u
    };

    // 8 is the ancestor of 4(ancestor of 4)
    for (int i = 1; i < LOG; i++) {
        for (int u = 1; u <= n; u++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }
    }
    auto kth_anc = [&](int u, int k) {
        for (int i = 0; i < LOG; i++) {
            if (((1 << i) & k)) {
                u = up[i][u];
            }
        }
        return u;
        // exp like 3 11 means get the first anc --> get the second of the first ancestor
    };
    while (m--) {
        ll u, v;
        cin >> u >> v;
        cout << lca(u, v) << el;
    }

}

signed main() {
    MO();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
