 
const int N = 100 + 5;
const int inf = 2e9 + 10;
 
int n;
int m;
int d[N][N];

/*
    * inicializar el arreglo d con INF, a menos que i == j 
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			d[i][j] = i == j ? 0 : inf;
		}
	}
    * para escoger siempre la menor 
    * arista en caso de aristas múltiples
	for(int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		d[u][v] = min(d[u][v], w);
	}
*/

bool floyd_warshall(){
    for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(d[i][k] == inf || d[k][j] == inf) continue;
				if(d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

	// Termina Floyd-Warshall
	// comprobacion de ciclos negativos
    for(int i = 0; i < n; i++) {
		if(d[i][i] < 0) {
			return false;
		}
	}
    return true; 
}