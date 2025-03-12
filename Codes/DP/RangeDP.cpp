vector<int> cost(n + 2);
for(int i = 1; i <= n; i++) cin >> cost[i]; 

vector<vector<int>> seg(n + 2);
for(int i = 0; i < m; i++){
    int l, r; cin >> l >> r;
    seg[r].emplace_back(l);
}

vector<int> last(n + 2);
int curr = 0;

for(int i = 1; i <= n + 1; i++){
    for(auto l : seg[i - 1]) curr = max(l, curr);
    last[i] = curr;
}


SegmentTree dp(n + 2);
for(int r = 1; r <= n + 1; r++){
    long long now = 1LL * cost[r] + dp.query(last[r], r);
    dp.upd(r, now);
}

cout << dp.query(n + 1, n + 2) << "\n";