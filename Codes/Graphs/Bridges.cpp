int n; // para guardar el numero de vertices
int m; // aristas
int k; // numero de componentes 2-conexas en el arbol final 
int C[N];  // componente de cada vertice
int to[N], from[N]; // vertice de salida y llegada para cada arista
int timer; // para el DFS 
int low[N];
int tin[N];
bool vis[N];
bool bridge[N]; // es puente ? 
vector<int> T[N]; // arbol final
vector<pair<int, int>> G[N]; // first = v, second = id de arista 
 
void DFS(int u, int p = -1) {
	vis[u] = true;
	low[u] = tin[u] = timer++;
	for(auto edge : G[u]) {
		int v, e;
		tie(v, e) = edge;
		if(v == p) continue;
		if(vis[v]) {
			low[u] = min(low[u], tin[v]);
		}
		else {
			DFS(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > tin[u]) {
				bridge[e] = true;
			}
		}
	}
}

void build_tree() {
	DFS(1);
	for(int i = 1; i <= n; i++) vis[i] = false;
	k = 0;
	for(int i = 1; i <= n; i++) {
		if(vis[i]) continue;
		queue<int> Q;
		Q.emplace(i);
		vis[i] = true;
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			C[u] = k;
			for(auto edge : G[u]) {
				int v, e;
				tie(v, e) = edge;
				if(bridge[e]) continue;
				if(vis[v]) continue;
				Q.emplace(v);
				vis[v] = true;
			}
		}
		k += 1;
	}
	for(int i = 1; i <= m; i++) {
		if(not bridge[i]) continue;
		int u = C[to[i]], v = C[from[i]];
		T[u].emplace_back(v);
		T[v].emplace_back(u);
	}
}