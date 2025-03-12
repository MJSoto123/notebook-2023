struct SuffixAutomaton {
	int nodes;
	vector<int> link; // suffix link
	vector<int> len; // max length of the state
	vector<int> firstpos; // last position of first occurrence of state
	vector<vector<int>> nxt; // transitions
	vector<bool> is_clone; // clone attribute (for counting)

	SuffixAutomaton() {
		len.emplace_back(0);
		link.emplace_back(-1);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(-1);
		is_clone.emplace_back(false);
		nodes = 1;
	}

	void add_node(int new_len, int new_link, int new_fp, bool new_clone) {
		len.emplace_back(new_len);
		link.emplace_back(new_link);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(new_fp);
		is_clone.emplace_back(new_clone);
	}

	int add(int p, int c) {
		auto getNxt = [&] () {
			if (p == -1) return 0;
			int q = nxt[p][c]; 
			if (len[p] + 1 == len[q]) return q;
			int clone = nodes++;
			add_node(len[p] + 1, link[q], firstpos[q], true);
			nxt[nodes - 1] = nxt[q];
			link[q] = clone;
			while(~p and nxt[p][c] == q) {
				nxt[p][c] = clone;
				p = link[p];
			}
			return clone;
		};
		// if (nxt[p][c]) return getNxt();
		// ^ need if adding > 1 string
		int cur = nodes++; // make new state
		add_node(len[p] + 1, -1, firstpos[p] + 1, false);
		while(~p and !nxt[p][c]) {
			nxt[p][c] = cur;
			p = link[p];
		}
		int x = getNxt(); 
		link[cur] = x; 
		return cur;
	}

	void init(string s) { // add string to automaton
		int p = 0; 
		for(auto c : s) {
			p = add(p, c - 'a');
		}
	} 
 
    void prepro() {
        vector<int> topo_order(nodes);
        iota(topo_order.begin(), topo_order.end(), 0);
        sort(topo_order.begin(), topo_order.end(), [&](int a, int b) {
            return len[a] > len[b];
        });
    
        cnt.assign(nodes, 0);
        for (int u : topo_order) {
            for (int c = 0; c < 26; c++) {
                int v = nxt[u][c];
                if (v) cnt[u] += cnt[v];
            }
            cnt[u]++;
        }
    }
 
    string get_kth(int k) {
        int u = 0;
        string result = "";
 
        while (k > 0) {
            for (int c = 0; c < 26; c++) {
                if (nxt[u][c]) {
                    int v = nxt[u][c];
                    if (cnt[v] >= k) {
                        result += char(c + 'a');
                        k--;
                        u = v;
                        break;
                    } else {
                        k -= cnt[v];
                    }
                }
            }
        }
 
        return result;
    }
};