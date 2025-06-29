vector<int> suffix_array(string s) {
    s += '$';
    const int A = 256;
    int n = s.size(), cls = 1;
    vector<int> p(n), c(n), cnt(max(A, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < A; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) ++cls;
        c[p[i]] = cls - 1;
    }
    vector<int> pn(n), cn(n);
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(begin(cnt), begin(cnt) + cls, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < cls; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cls = 1;
        cn[p[0]] = 0;
        auto prv = make_pair(c[p[0]], c[(p[0] + (1 << k)) % n]);
        for (int i = 1; i < n; i++) {
            auto cur = make_pair(c[p[i]], c[(p[i] + (1 << k)) % n]);
            if (cur != prv) ++cls;
            cn[p[i]] = cls - 1;
            swap(prv, cur);
        }
        swap(c, cn);
    }
    return p;
}
vector<int> get_lcp(const string &s, const vector<int> &p) {
    int n = s.size();
    vector<int> pos(n), lcp(n);
    for (int i = 1; i <= n; i++) pos[p[i]] = i - 1;
    int k = 0;
    for (int i = 0; i < n; i++) {
        int j = p[pos[i]];
        while (s[i + k] == s[j + k]) k++;
        lcp[pos[i]] = k;
        k = max(k - 1, 0);
    }
    return lcp;
}