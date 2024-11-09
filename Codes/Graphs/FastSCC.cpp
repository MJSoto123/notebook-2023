struct TarjanSCC {
    vvi G;  // Lista de adyacencia
    vi st, low, num; 
    vi comp; 
    int n, timer; 
    int num_comps;

    TarjanSCC(int n_) : n(n_), num_comps(0) {
        G.resize(n);
        comp.assign(n, -1);
        low.resize(n);
        num.assign(n, -1);
        st.clear();
        timer = num_comps = 0; 
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
    }

    void DFS(int u) {
        num[u] = low[u] = timer++; 
        st.push_back(u);
        for(int v : G[u]) {
            if(num[v] == -1) {
                DFS(v);
                low[u] = min(low[u], low[v]);
            }else if(comp[v] == -1) low[u] = min(low[u], low[v]);
        }

        if(num[u] == low[u]) {
            int y = st.back();
            do {
                y = st.back();
                comp[y] = num_comps; 
                st.pop_back();
            } while(y != u);
            num_comps++; 
        }

    }

    void build_SCC() {
        for(int i = 0; i < n; i++) {
            if(num[i] == -1) DFS(i);
        }
    }

};


struct SCC {
    vvi G;  // Lista de adyacencia
    vvi Gt; // Grafo transpuesto  
    vi order; // para ordenar por tiempo de salida en dfs1
    vi comp; 
    vector<bool> vis;
    int n; 
    int num_comps; 
    SCC(int n_) : n(n_), num_comps(0) {
        G.resize(n);
        Gt.resize(n);
        vis.assign(n, false);
        comp.assign(n, -1);
    }
 
    void add_edge(int u, int v) {
        G[u].push_back(v);
        Gt[v].push_back(u);
    }
 
    void DFS1(int u) {
        vis[u] = true; 
        for(int v : G[u]) {
            if(vis[v]) continue;
            DFS1(v);
        }
        order.emplace_back(u);
    }
 
    void DFS2(int u, int comp_id) {
        vis[u] = true; 
        for(int v : Gt[u]) {
            if(vis[v]) continue;
            DFS2(v, comp_id);
        }
        comp[u] = comp_id; 
    }
 
    void build_SCC() {
        // Ordenar por tiempo de salida 
        for(int i = 0; i < n; i++) {
            if(vis[i]) continue;
            DFS1(i);
        }
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), false);
        int cur_comp_id = 0; 
        for(int i : order) {
            if(vis[i]) continue;
            DFS2(i, cur_comp_id);
            cur_comp_id++; 
        }
        num_comps = cur_comp_id; 
    }
 
};