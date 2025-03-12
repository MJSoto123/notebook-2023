int n, m;
vector<long long> a, prefix, dp_before, dp_cur;

// Segment Cost [i, j] = (sm_{i..j})^2
long long C(int i, int j) {
    long long sum = prefix[j + 1] - prefix[i];
    return sum * sum;
}

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); ++k) {
        long long cost = (k ? dp_before[k - 1] : 0);
        if (cost != LLONG_MAX)
            best = min(best, {cost + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

long long solve() {
    dp_before.assign(n, LLONG_MAX);
    dp_cur.assign(n, 0);

    for (int i = 0; i < n; ++i)
        dp_before[i] = C(0, i);

    for (int i = 1; i < m; ++i) {
        compute(0, n - 1, 0, n - 1);
        dp_before = dp_cur;
    }

    return dp_before[n - 1];
}