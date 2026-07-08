class Solution {
public:
    static const int MOD = 1000000007;

    struct Node {
        long long val;
        int cnt;
        Node(long long v = 0, int c = 0) : val(v), cnt(c) {}
    };

    vector<Node> seg;
    vector<long long> pow10;

    Node merge(Node a, Node b) {
        return Node((a.val * pow10[b.cnt] + b.val) % MOD,
                    a.cnt + b.cnt);
    }

    void build(int idx, int l, int r, string &s) {
        if (l == r) {
            if (s[l] == '0')
                seg[idx] = Node(0, 0);
            else
                seg[idx] = Node(s[l] - '0', 1);
            return;
        }

        int mid = (l + r) / 2;
        build(idx * 2, l, mid, s);
        build(idx * 2 + 1, mid + 1, r, s);
        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(idx * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(idx * 2 + 1, mid + 1, r, ql, qr);

        return merge(
            query(idx * 2, l, mid, ql, qr),
            query(idx * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        pow10.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i];
            if (s[i] != '0')
                prefixSum[i + 1] += s[i] - '0';
        }

        seg.assign(4 * n + 4, Node());
        build(1, 0, n - 1, s);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            Node cur = query(1, 0, n - 1, l, r);
            long long sum = prefixSum[r + 1] - prefixSum[l];

            ans.push_back((cur.val * sum) % MOD);
        }

        return ans;
    }
};