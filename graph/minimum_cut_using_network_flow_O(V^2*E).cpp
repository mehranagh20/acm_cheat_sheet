// minimum cut is problem of minimizing the amount of capacity of edges that are going to be removed in order to 
// the max flow from source to destination is 0.

// the idea of alg : after running max flow alg, run dfs from source and use edges with positive weight to traverse
// the graph, all edges from visited verteces to unvisited ones are edges to be removed for minimum cut. 


vi dist, work;
int s, t, n; // s -> source, t -> destination, n -> number of verteces.
vvi rem, graph; // rem is n * n vec with capacity of edges, graph is adjList representation of graph.

bool dinic_bfs() {
    dist.clear(); dist.resize(n, -1); dist[s] = 0;
    queue<int> queue1; queue1.push(s);
    while(!queue1.empty()) {
        int u = queue1.front(); queue1.pop();
        for(auto &e : graph[u]) {
            if(dist[e] != -1 || rem[u][e] <= 0) continue;
            dist[e] = dist[u] + 1;
            queue1.push(e);
        }
    }
    return (dist[t] != -1);
}

int dinic_dfs(int u, int f) {
    if(u == t) return f;
    for(int &i = work[u]; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(rem[u][v] <= 0) continue;
        if(dist[u] + 1 == dist[v]) {
            int df = dinic_dfs(v, min(f, rem[u][v]));
            if(df > 0) {
                rem[v][u] += df;
                rem[u][v] -= df;
                return df;
            }
        }
    }
    return 0;
}

int maxFlow() {
    int result = 0;
    while(dinic_bfs()) {
        work.clear(); work.resize(n, 0);
        while(int d = dinic_dfs(s, inf)) result += d;
    }
    return result;
}

void dfs(vi &vis, int a) {
    vis[a] = 1;
    for(auto &e : graph[a]) if(!vis[e] && rem[a][e]) dfs(vis, e);
}


// inside main
int mx = maxFlow();
vi vis(n, s); dfs(vis, s); // running dfs from source.
for(int i = 0; i < vis.size(); i++) if(vis[i]) {
    for(auto &ee : graph[i])
       if(!vis[ee]); // (i + 1) to (ee + 1) is an edge in minimum cut.
}
