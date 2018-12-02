// O(NlogN) for preprocessing, and O(logN) for each LCA query

int n, l, timer; // only assign n equal to # of vertices in main
vvi adj, up; // also Adjacency list :)
vi tin, tout;

void dfs(int v, int p){
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (auto u : adj[v]) if (u != p) dfs(u, v);
    tout[v] = ++timer;
}

bool is_ancetor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v){
    if (is_ancetor(u, v)) return u;
    if (is_ancetor(v, u)) return v;
    
    for (int i = l; i >= 0; --i)
        if (!is_ancetor(up[u][i], v))
            u = up[u][i];
    
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n), tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vi(l + 1));
    dfs(root, root);
}
