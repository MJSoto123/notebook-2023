vi get(ll n) {
    vi dig(19, 0);
    for (int i = 18; i >= 0; i--) {
        dig[i] = n % 10;
        n /= 10;
    }
    return dig;
}

vi high;
ll dp[19][50][2];
vi cnt(10);

void init() { memset(dp, -1, sizeof(dp)); }

ll dfs(int pos = 0, bool smaller = 0, int inv = 0, bool positive = 0) {
    if (pos == 19) {
        return inv;
    }
    if (smaller && dp[pos][inv][positive] != -1) return dp[pos][inv][positive];

    ll res = 0;
    int mx_digit = smaller ? 9 : high[pos];

    for (int dig = 0; dig <= mx_digit; dig++) {
        int add = 0;
        for (int i = dig - 1; i >= 0; i--) add += cnt[i];
        if(dig || positive) cnt[dig]++;
        res += dfs(
            pos + 1,
            smaller || (dig < mx_digit),
            inv + add,
            positive || dig
        );
        if(dig || positive) cnt[dig]--;
    }

    return smaller ? dp[pos][inv][positive] = res : res;
}

void solve(){
    ll a, b; cin >> a >> b;

    init();
    high = get(a - 1);
    ll dpa = dfs();

    init();
    high = get(b);
    ll dpb = dfs();
    cout << dpb - dpa << endl;
}