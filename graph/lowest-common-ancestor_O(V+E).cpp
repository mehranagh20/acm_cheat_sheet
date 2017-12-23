#define MAX_N 1000

vvi children;

int L[2*MAX_N], E[2*MAX_N], H[MAX_N], idx;

void dfs(int cur, int depth) {
  H[cur] = idx;
  E[idx] = cur;
  L[idx++] = depth;
  for (int i = 0; i < children[cur].size(); i++) {
    dfs(children[cur][i], depth+1);
    E[idx] = cur; // backtrack to current node
    L[idx++] = depth;
  }
}

void buildRMQ() {
  idx = 0;
  memset(H, -1, sizeof H);
  dfs(0, 0); // we assume that the root is at index 0
}

// inside main():
// H[u] < H[v] (swap u and v otherwise)
// RMQ must be on array 'L'
RMQ rmq; rmq.init(L);
while(cin >> a >> b) { // get LCA of node 'a' and 'b'
        if(H[a] >= H[b]) swap(a, b);
        cout << E[rmq.range_minimum_query(H[a], H[b]).second] << endl; // second element of rmq query is the index of min element
}
