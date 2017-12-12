vi match, vis;
// global variables
int Aug(int l) {
// return 1 if an augmenting path is found
    if (vis[l]) return 0;
// return 0 otherwise
    vis[l] = 1;
    for (int j = 0; j < (int)AdjList[l].size(); j++) {
        int r = AdjList[l][j]; // edge weight not needed -> vector<vi> AdjList
        if (match[r] == -1 || Aug(match[r])) {
            match[r] = l; return 1;
// found 1 matching
        } }
    return 0;
// no matching
}
// inside int main()
// build unweighted bipartite graph with directed edge left->right set
int MCBM = 0;
match.assign(V, -1);
// V is the number of vertices in bipartite graph
for (int l = 0; l < n; l++) {
// n = size of the left set
vis.assign(n, 0);
// reset before each recursion
MCBM += Aug(l);
}
printf("Found %d matchings\n", MCBM);
