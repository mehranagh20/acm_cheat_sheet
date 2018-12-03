// O(VE + V^2√E) , worst case is O(V^3)

int n; // # of vertices
vvi capacity, flow;
vi height, excess;

void push(int u, int v){
    auto d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d, flow[v][u] -= d;
    excess[u] -= d, excess[v] += d;
}

void relabel(int u){
    ll d = inf;
    forn(i, n){
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    
    if (d < inf) height[u] = d + 1;
}

vi find_max_height_vertices(int s, int t) {
    vi max_height;
    forn(i, n) {
        if (i != s && i != t && excess[i] > 0) {
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear();
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i);
        }
    }
    return max_height;
}

ll max_flow(int s, int t){
    height.assign(n, 0); height[s] = n;
    flow.assign(n, vi(n, 0));
    excess.assign(n, 0); excess[s] = inf;  
    forn(i, n) if (i != s) push(s, i);

    vi current;
    while ((current = find_max_height_vertices(s, t)).size()) {
        for(auto i : current) {
            bool pushed = false;
            for (int j = 0; j < n && excess[i]; j++) {
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1)
                    push(i, j), pushed = true;   
            }
            
            if (!pushed) { relabel(i); break; }
        }
    }

    ll max_flow = 0;
    forn(i, n) max_flow += flow[s][i];
    return max_flow;
}
