// dijkstra alg for finding SSSP on graph.
// shortest path of all verteces from s is in dist.
// AdjList holds adjacency representation of graph.

	vi dist(n, inf); dist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0, s));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // this is a very important check
        for (int j = 0; j < (int) AdjList[u].size(); j++) {
            ii v = AdjList[u][j];
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push(ii(dist[v.first], v.first));
            }
        }
    }

