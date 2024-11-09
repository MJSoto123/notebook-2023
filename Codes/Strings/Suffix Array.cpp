struct SuffixArray {
	vi sa, lcp;
    string s; 
	SuffixArray(string& s_, int lim=256) : s(s_) { // or basic_string<int>
        int n = s.size() + 1, k = 0, a, b;
		vi x(s.begin(), s.end()), y(n), ws(max(n, lim)), rank(n);
		x.push_back(0), sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        s.push_back('$');
		for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(y.begin(), y.end(), n - j);
			for(int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(ws.begin(), ws.end(), 0);
			for(int i = 0; i < n; i++) ws[x[i]]++;
			for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for(int i = 1; i < n; i++) {
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
		}
		for(int i = 1; i < n; i++) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);

	}
    
    //Longest Common Substring: construir el suffixArray s = s1 + "#" + s2 + "$" y m = s2.size()
    // pair<int, int> lcs() {
    //     int mx = -1, ind = -1;
    //     for (int i = 1; i < n; i++) {
    //         if (((sa[i] < n-m-1) != (sa[i-1] < n-m-1)) && mx < lcp[i]) {
    //             mx = lcp[i]; ind = i;
    //         }
    //     }
    //     return {mx, ind};
    // }

};
