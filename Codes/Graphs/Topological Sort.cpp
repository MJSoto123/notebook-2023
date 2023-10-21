vector<int> toposort(int n, int m, vector<vector<int>> &G) {
	vector<int> in_degree(n, 0);
	for(int i = 0; i < n; i++) {
		for(int v : G[i]) in_degree[v] += 1;
	}
	queue<int> Q;
	vector<int> res;
	for(int i = 0; i < n; i++) {
		if(in_degree[i] == 0) {
			Q.emplace(i);
		}
	}
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		res.emplace_back(u);
		for(int v : G[u]) {
			in_degree[v] -= 1;
			if(in_degree[v] == 0) {
				Q.emplace(v);
			}
		}
	}
	return res.size() < n ? vector<int>() : res;
}