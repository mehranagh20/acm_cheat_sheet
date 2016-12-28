// kruskal alg for finding minimum spanning tree.
// kruskal func will return the amount of MST, you can modify it to get the real MSP representation.

//Variants:
// 1. for finding maximum spanning tree just multiply weights of edges by -1 and run the alg.

// 2. for finding minimum spanning forest just consider this : every time an edge is taken number of components decreases by one, so run the alg and take edges while number of components are less that the desired number of components.

// 3. in order to find minimum spanning subgraph, just add fixed edges to ufds and run the alg.

// 4. in order to find second best spanning tree, first find MST, after that for each edge in MST temporary set it off so the kruskal alg wont select it, do this for every edge in MST and the best answer is second best spanning tree.

// 5. minmax is problem of finding minimum of maximum of edge weights among all possible pahts between i, j. in order to find min max (or maxmin) run the Kruskal alg and save the MST representation then traversing from i to j and finding the maximum weight is the answer.



vector<int> ufds;
vector<pair<int, ii>> graph;

void buildUfds(int n) {
    ufds.clear(); ufds.resize(n);
    for(int i = 0; i < n; i++) ufds[i] = i;
}

int findSet(int i) {
    return (ufds[i] == i) ? i : (ufds[i] = findSet(ufds[i]));
}

bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

void joinSets(int i, int j) {
    int a = findSet(i), b = findSet(j);
    if (a < b) ufds[a] = b;
    else ufds[b] = a;
}

int kruskal() {
    int cost = 0;
    for(int i = 0; i < graph.size(); i++) {
        pair<int, ii> fr = graph[i];
        if(!isSameSet(fr.second.first, fr.second.second)) {
            cost += fr.first;
            joinSets(fr.second.second, fr.second.first);
        }
    }
    return cost;
}

// in main:
// sort edge list base on weight assending then call buildUfds(n) where n is number of verteces before calling kruskal alg.
