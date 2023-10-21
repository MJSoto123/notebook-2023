int n;
int m;
bool in[N];
bool vis[N];
int comp[N];
vector<int> order;
vector<int> component;
vector<int> G[2][N]; // en G[1] es el grafo transpuesto 
 
void DFS(int id, int u) {
	vis[u] = id ^ 1;
	for(int v : G[id][u]) {
		if(vis[v] == (id ^ 1)) continue;
		DFS(id, v);
	}
	if(id == 0) order.emplace_back(u);
	else component.emplace_back(u);
}
 
int solve() {
	order.clear();
	component.clear();
	for(int i = 0; i < n; i++) {
		if(vis[i]) continue;
		DFS(0, i);
	}
	reverse(order.begin(), order.end());
	vector<vector<int>> res;
	for(int u : order) {
		if(not vis[u]) continue;
		component.clear();
		DFS(1, u);
		for(int x : component) comp[x] = res.size();
		res.emplace_back(component);
	}
	for(int i = 0; i < n; i++) {
		for(int v : G[0][i]) {
			if(comp[i] == comp[v]) continue;
			in[comp[v]] = true;
		}
	}
	int cnt = 0;
	for(int i = 0; i < res.size(); i++) cnt += !in[i];
	return cnt;
}