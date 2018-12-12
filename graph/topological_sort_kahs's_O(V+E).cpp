// n = # of vertexes. indegree stores number of incoming edges to i'th vertex.
// fill n and calculate indegree before running alg. ts holds the Topsort

vi indegree(n, 0), vis(n, 0), ts;

priority_queue<int, vi, greater<int>> pq; 
forn(i, n) if(!indegree[i]) pq.push(i);
while(!pq.empty()) {
    int top = pq.top(); pq.pop();
    vis[top] = 1; ts.push_back(top);
    for(auto &e : graph[top]) {
        if(vis[e]) continue;
        indegree[e]--;
        if(!indegree[e]) pq.push(e);
    }
}
