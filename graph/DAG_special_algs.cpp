// 1. Single Source shortest(longest) path on DAG:
// in order to find sssp of DAG just find one valid topological sort of the DAG (there is allways at least one
// valid topological sort in dag), then relax all outgoing edges of these vertices base on found Top sort
// complexity of this alg is O(V + E) of finding top sort
void topSort(vi &order, int v, vi &vis, vvi &graph) {
    vis[v] = 1;
    for(auto &e : graph[v]) if(!vis[e]) topSort(order, e, vis, graph);
    order.push_back(v);
}

// inside main
// graph is adjList.
vi order, vis(n, 0), dis(n, inf); dis[s] = 0; // n is number of vertices. dis holds distance of every vertec from s.
for(int i = 0; i < n; i++) if(!vis[i])
    topSort(order, i, vis, graph);
for(int i = order.size() - 1; i >= 0; i--) for(auto &e : graph[order[i]]) {
    if(dis[order[i]] != inf) // after this alg if vertec i is not connected to s dis[i] is inf.
        dis[e.first] = dis[order[i]] + e.second;
}





// 2. counting paths on DAG:
// this alg is for finding number of paths from a source vertex to other vertices.

void topSort(vi &order, int v, vi &vis, vvi &graph) {
    vis[v] = 1;
    for(auto &e : graph[v]) if(!vis[e]) topSort(order, e, vis, graph);
    order.push_back(v);
}
// in main()
// graph holds the DAG.
vi order, vis(n, 0), ways(n, 0);
ways[s] = 1; // setting starting point's number of paths to 1. s is the starting point.
for(int i = 0; i < n; i++) if(!vis[i]) // in case that graph is not garaunted to be connected.
	topSort(order, 0, vis, graph); // finding a valid top sort.
for(int i = order.size() - 1; i >= 0; i--) { // topSort alg stores the order in reverse order.
    int n = order[i];
    for(auto &e : graph[n]) ways[e] += ways[n];
}



