int solve() {
    sort(cuts.begin(), cuts.end());

    int N = n + 2;
    int dp[N][N], opt[N][N];

    auto C = [&](int i, int j) {
        return cuts[j] - cuts[i];
    };

    // Inicialización base
    for (int i = 0; i < N; ++i) {
        dp[i][i] = 0;
        if (i + 1 < N) {
            dp[i][i + 1] = 0;
            opt[i][i + 1] = i + 1;
        }
    }

    // DP con Knuth Optimization
    for (int i = N - 2; i >= 0; i--) {
        for (int j = i + 2; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                int val = dp[i][k] + dp[k][j] + cost;
                if (val < mn) {
                    mn = val;
                    opt[i][j] = k;
                }
            }
            dp[i][j] = mn;
        }
    }

    return dp[0][N-1];
}