// Bellman Ford alg is used for finding single source shortest path for small graphs with O(E * V)
// it is also used to detect negative circle in graph.
// s is the source.


vi dist(n, inf); dist[s] = 0; // holds the distance
for(int i = 0; i < n - 1; i++) {
    bool up = false; // used to prune before finishing when no update is neccessary.
    for (int j = 0; j < n; j++)
        for (auto &e : AdjList[j]) if(dist[e.first] > e.second + dist[j]) {
                up = true; dist[e.first] = e.second + dist[j];
            }
    if(!up) break;
}

// this part is used to detect negative circle, if hasNegCircle is true, graph has negative circle.
bool hasNegCircle = false;
for(int j = 0; j < n && !hasNegCircle; j++) for(auto &e : AdjList[j])
        if(dist[e.first] > e.second + dist[j]) {
            hasNegCircle = true;
            break;
        }

/*****************************************************/

// Shortest Path Faster Algorithm(SPFA)
// utilizes a queue to eliminate redundant operations in Bellman Ford’s algorithm.

vi dist(n, inf), inQ(n, 0), visit(n, 0);
    dist[s] = 0, inQ[s] = visit[s] = 1;
    queue<int> q; q.push(s);


while (!q.empty()) {
    int u = q.front(); q.pop(); inQ[u] = 0;
    for(auto &e: AdjList[u]){
        int v = e.first, w = e.second;
        if (dist[u] + w < dist[v]) { // if can relax
            dist[v] = dist[u] + w; // relax
            if (!inQ[v]) { // add to the queue
                q.push(v); // only if it is not already in the queue
                inQ[v] = 1, visit[v]++;
            }
        }
    }
}

// this part is used to detect negative circle, if hasNegCircle is true, graph has negative circle.
bool hasNegCircle = false;
for (int i = 0; i < n && !hasNegCircle; ++i)
    if(visit[i] > n - 1)
        hasNegCircle = true;

