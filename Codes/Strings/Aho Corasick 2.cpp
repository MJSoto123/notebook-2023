const int N = 1e6 + 10;
const int sigma = 30;
int term[N], suflink[N], trie[N][sigma];
vi tree[N];
bool vis[N], ans[N];
int sz = 0; 
 
// dsu
int par[N];
int get(int a) {return a == par[a] ? a : par[a] = get(par[a]); }
void unite(int a, int b) {
    a = get(a); b = get(b);
    if(a == b) return; 
    par[a] = b; 
}
 
void add_trie(const string &s, int id) {
    int node = 0;
    for(char c : s) {
        int now = c - 'a';
        if(!trie[node][now]) trie[node][now] = ++sz;
        int last = node; 
		node = trie[node][now];
    }
    if(term[node]) unite(term[node], id);
    else term[node] = id;
}
 
void BFS(int src) {
    queue<int> q;
	q.push(src);
    while(q.size()) {
        int v = q.front(); q.pop();
        int u = suflink[v];
        if(v) tree[u].push_back(v);
        for(int c = 0; c < sigma; c++) {
            if(trie[v][c]) {
				suflink[trie[v][c]] = (v == 0 ? 0 : trie[u][c]);
				q.push(trie[v][c]);
            }else trie[v][c] = (v == 0 ? 0 : trie[u][c]);
        }
    }
}
 
bool DFS(int src) {
    bool exists = vis[src];
    for(int u : tree[src]) exists |= DFS(u);
    return ans[get(term[src])] = exists; 
}