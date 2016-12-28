   // this BFS modified alg will find shortest path from s to every other verteces in O(E + V) 
   // AdjList holds the adjacency list representation of graph.
   // p holds parent of each vertex in shortest path, it is possible to print the path with p vector.
   // distances are in dist.


    // inside int main()
    vi dist(n, inf); dist[s] = 0; // distance from source s to s is 0
    queue<int> q; q.push(s);
    vi p;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int j = 0; j < (int) AdjList[u].size(); j++) {
            ii v = AdjList[u][j];
            if (dist[v.first] == inf) {
                dist[v.first] = dist[u] + 1;
                p[v.first] = u;
                q.push(v.first);
            }
        }
    }
