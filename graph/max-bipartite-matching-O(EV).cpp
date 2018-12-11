vi match, vis; // global variables
int Aug(int l) {
    // return 1 if an augmenting path is found, 0 otherwise
    if (vis[l]) return 0;

    vis[l] = 1;
    for(auto r: AdjList[l]) {
        if (match[r] == -1 || Aug(match[r])) { // found 1 matching
            match[r] = l; return 1;         
        } }
    return 0; // no matching
}

// inside main
// build unweighted bipartite graph with directed edge left->right set
// V is the number of vertices in bipartite graph
// n = size of the left set

int MCBM = 0;
match.assign(V, -1);
forn(l, n) { vis.assign(n, 0); MCBM += Aug(l); }
printf("Found %d matchings\n", MCBM);
