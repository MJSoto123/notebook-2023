// Prim clásico, retorna el MST de un grafo 

int n;
int m;
int q[N];
bool vis[N];
int wedge[N];
vector<pair<int, int>> G[N];
 
int Prim(int src) {
	memset(wedge, -1, sizeof wedge);
	wedge[src] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.emplace(0, src);
	while(!Q.empty()) {
		int we, u;
		tie(we, u) = Q.top(); Q.pop();
		vis[u] = true;
		for(auto e : G[u]) {
			int v, w;
			tie(v, w) = e;
			if(wedge[v] == -1 or wedge[v] > w) {
				wedge[v] = w;
				Q.emplace(wedge[v], v);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		if(not vis[i]) return -1;
	}
	return accumulate(wedge + 1, wedge + n + 1, 0);
}



/*
 *  
 *  Caso especial para un grafo completo 
 *  no es posible construir el grafo (memoria) 
 *  pero es posible un algoritmo O(n^2) 
 * 
 */
int n;
int x[N];
int y[N];
bool vis[N];
int edge[N]; // Minima arista que cruza desde S hasta mi nodo

int dis(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}
 
int Prim(int src) {
	vis[src] = true;
	for(int i = 0; i < n; i++) edge[i] = dis(src, i);
	for(int i = 1; i < n; i++) {
		// El nodo al que llega la arista ligera es al argmin(edge[i]) pero con vis[i] = false
		int v = -1;
		for(int j = 0; j < n; j++) {
			if(vis[j]) continue;
			if(v == -1 or edge[v] > edge[j]) v = j;
		}
		vis[v] = true;
		for(int j = 0; j < n; j++) {
			if(vis[j]) continue;
			edge[j] = min(edge[j], dis(v, j));
		}
	}
	return accumulate(edge, edge + n, 0);
}
