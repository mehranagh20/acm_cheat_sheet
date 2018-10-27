const int N = 1e4 + 10; // max of nodes
int n;
vvi g; // the tree
ll nxt[N], depth[N], tt, sz[N], in[N], out[N], rin[N], p[N];
int cst2[N + 10];

// some segment tree code here!

void dfs_sz(int v = 0, int par = 0, int dpth = 0) {
    sz[v] = 1, p[v] = par, depth[v] = dpth;
    for (auto &u: g[v]) {
        if (u.first != par) {
            dfs_sz(u.first, v, dpth + 1);
            sz[v] += sz[u.first];
            if (sz[u.first] > sz[g[v][0].first])
                swap(u, g[v][0]);
        }
    }
}

// nxt[x] ==> head of segment which x belongs to
// [in[nxt[v]], in[v]] ==> path from head of path which contains 'v' to 'v'
// [in[v], out[v]) == > subtree of 'v', pay attention to right )
void dfs_hld(int v = 0, int par = 0, int cst = 0) { // change cst in case of other operations if needed
    in[v] = tt++;
    rin[in[v]] = v;

    // modify in case of vertex query!
    cst2[in[v]] = cst; // setting cost of this edge(par --> v) in array which segment tree build is called upon it
    for (auto u: g[v]) {
        if (u.first != par) {
            nxt[u.first] = (u.first == g[v][0].first ? nxt[v] : u.first);
            dfs_hld(u.first, v, u.second);
        }
    }
    out[v] = tt;
}

ll crawl(ll u, ll v) { // path query
    ll ans = -1000000000LL; // we want max of a path, so we initialize this way
    while (nxt[u] != nxt[v]) {
        if (depth[nxt[u]] < depth[nxt[v]]) swap(u, v);
        ans = max(ans, go(1, 0, n - 1, in[nxt[u]], in[u])); // go is get function of segment tree
        u = p[nxt[u]];
    }
    if (in[v] > in[u]) swap(v, u);
    return max(ans, go(1, 0, n - 1, in[v] + 1, in[u])); // in case of node queries remove +1 because even the head matters
}

void modify(int a, int b) {
    upd(1, 0, n - 1, in[a], b); segment tree update
}

int main() {
    // get input here ...
    dfs_sz();
    dfs_hld();
    build(1, 0, n - 1); // build segment tree for tree with n nodes

    // query part:
    // ask query, one based
    int a, b; cin >> a >> b; a--, b--;
    cout << crawl(a, b) << endl;

    // update a'th edge to 'b'
    cin >> a >> b; a--;
    // if query is on nodes, then just use the actual node to update
    int u = edges[a].first, v = edges[a].second;
    // we assume the node with higher depth to be representative of the edge
    if (depth[u] > depth[v]) modify(u, b); // depth is valued after running dfs
    else modify(v, b);
}
