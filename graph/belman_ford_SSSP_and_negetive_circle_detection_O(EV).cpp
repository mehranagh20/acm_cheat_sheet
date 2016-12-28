// belman ford alg is used for finding single source shortest path for small graphs with O(E * V)
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
