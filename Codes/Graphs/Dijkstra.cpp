int n;
int m;
int D[N];
vector<pair<int, int>> G[N];
 

// las distancias mínimas se guardan en D
// indexa en 0  
void Dijkstra(int src) {
	for(int i = 0; i < n; i++) D[i] = -1;
	D[src] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q; // Min PQ
	Q.emplace(0, src);
	while(!Q.empty()) {
		int dis, u;
		tie(dis, u) = Q.top(); Q.pop();
		if(dis != D[u]) continue; // Verificacion de que u no ha sido visitado todavia
		for(auto e : G[u]) {
			int v, w;
			tie(v, w) = e;
			if(D[v] == -1 or D[v] > D[u] + w) {
				D[v] = D[u] + w;
				Q.emplace(D[v], v);
			}
		}
	}
}