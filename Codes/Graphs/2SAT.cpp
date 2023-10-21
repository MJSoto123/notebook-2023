struct SATSolver {
	// Assumes that nodes are 0-indexed
	int n;
	int m;
	vector<bool> vis;
	vector<int> comp;
	vector<int> order;
	vector<int> component;
	vector<vector<int>> G;
	vector<vector<int>> Gt;
 
	SATSolver(int n, int m) : n(n), m(m) {
		// X_i = 2i
		// ~X_i = 2i + 1
		comp.resize(2 * n);
		vis.resize(2 * n, false);
		G.resize(2 * n, vector<int>());
		Gt.resize(2 * n, vector<int>());
	}
 
	void add_edge(int u, int v) {
		// u OR v
		G[u ^ 1].emplace_back(v);
		G[v ^ 1].emplace_back(u);
		Gt[v].emplace_back(u ^ 1);
		Gt[u].emplace_back(v ^ 1);
	}
 
	void DFS1(int u) {
		vis[u] = true;
		for(int v : G[u]) {
			if(vis[v]) continue;
			DFS1(v);
		}
		order.emplace_back(u);
	}
 
	void DFS2(int u) {
		vis[u] = true;
		for(int v : Gt[u]) {
			if(vis[v]) continue;
			DFS2(v);
		}
		component.emplace_back(u);
	}
 
	void get_scc() {
		for(int i = 0; i < 2 * n; i++) {
			if(vis[i]) continue;
			DFS1(i);
		}
		reverse(order.begin(), order.end());
		fill(vis.begin(), vis.end(), false);
		int component_id = 0;
		for(int u : order) {
			if(vis[u]) continue;
			component.clear();
			DFS2(u);
			for(int x : component) comp[x] = component_id;
			component_id += 1;
		}
	}
 
	vector<int> solve() {
		vector<int> res(n);
		get_scc();
		for(int i = 0; i < n; i++) {
			int val = 2 * i;
			if(comp[val] == comp[val ^ 1]) return vector<int>();
			if(comp[val] < comp[val ^ 1]) res[i] = 0;
			else res[i] = 1;
		}
		return res;
	}
};