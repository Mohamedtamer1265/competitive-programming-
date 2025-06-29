 template <class T> struct sparsetable {
        int n, LOG;
        vector<vector<T>> st;

        T f(T a, T b) {
            return max(a, b);
        }

        sparsetable() {}

        sparsetable(vector<T> a) {
            n = a.size();
            LOG = __lg(n) + 1;
            st = vector<vector<T>>(n, vector<T>(LOG));
            for (int i = 0; i < n; i++) {
                st[i][0] = a[i];
            }
            for (int j = 1; j < LOG; j++) {
                for (int i = 0; i + (1 << j) <= n; i++) {
                    st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T query(int l, int r) {
            if (l > r) return INT_MIN;
            int k = __lg(r - l + 1);
            return f(st[l][k], st[r - (1 << k) + 1][k]);
        }
    };