// adj_rev stores the adjacency list for the graph in reversed form
// node with undefined state will lead to draw

vvi adj_rev;
vector<bool> winning, losing, vis;
vi degree; // must be calculated before run

void dfs(int v) {
    vis[v] = true;
    for (auto u : adj_rev[v]) {
        if (!vis[u]) {
            if (losing[v]) winning[u] = true;
            else if (--degree[u] == 0) losing[u] = true;
            else continue;
            dfs(u);
        }
    }
}
