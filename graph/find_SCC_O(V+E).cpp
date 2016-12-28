// finding Strongly Connected Components.
// numSCC holds the number of strongly connected components
// fill AdjList with the graph before running tarjanSCC alg.

vi dfs_num, dfs_low, S, visited;
int dfsNumberCounter, numSCC;
vvii AdjList;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
    S.push_back(u); // stores u in a vector based on order of visitation
    visited[u] = 1;
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j];
        if (dfs_num[v.first] == 0)
            tarjanSCC(v.first);
        if (visited[v.first])
            dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); }
    if (dfs_low[u] == dfs_num[u]) { // if this is a root (start) of an SCC
        printf("SCC %d:", ++numSCC); // printing this SCC, you can manipulate it as you want
        while (1) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            printf(" %d", v);
            if (u == v) break; }
        printf("\n");
    } }

// inside int main()
int main() {
    dfs_num.assign(V, 0); dfs_low.assign(V, 0); visited.assign(V, 0);
    dfsNumberCounter = numSCC = 0;
    for (int i = 0; i < V; i++)
        if (dfs_num[i] == 0)
            tarjanSCC(i);
} 
