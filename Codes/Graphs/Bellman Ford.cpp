int n;
int m;
int D[N]; // D[u] : Minima distancia de src a u usando <= k aristas en la k-ésima iteración
bool vis[N]; // vis[u] : El nodo se ha vuelto alcanzable por src
vector<tuple<int, int, int>> edges;

// retorna true si no hay ciclos negativos
bool bellman_ford(int src) {
	for(int i = 0; i < n; i++) {
		D[i] = -1;
		vis[i] = false;
	}
	D[src] = 0;
	vis[src] = true;
	for(int i = 1; i < n; i++) {
		for(auto e : edges) {
			int u, v, w;
			tie(u, v, w) = e;
			if(not vis[u]) continue;
			if(not vis[v] or D[v] > D[u] + w) {
				D[v] = D[u] + w;
				vis[v] = true;
			}
		}
	}
	for(auto e : edges) {
		int u, v, w;
		tie(u, v, w) = e;
		if(not vis[u]) continue;
		if(not vis[v] or D[v] > D[u] + w) {
			return false; // Ciclo negativo alcanzable por src
		}
	}
	return true;
}