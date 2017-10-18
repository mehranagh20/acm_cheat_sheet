// NOTE: edges must be bidirectional --> fi there is an edge from i to j, there must be an edge from j to i

// to find minimum cut, run flow, the max flow is the value of minimum cut, to find edges
// we put all reachable vertexes from source with positive weight to S components and all others to C
// all edges connecting S vertexes to C are in minimum edges vertexes set.

//Edmon's karp algo will find network max flow in O(V * E ^ 2). it is easier to code than dinic and good for graphs
//with not lots of edges.
//like dinic it is possible to construct the path using res 2D arr, if there is a path from i to j then res[j][i] > 0.

// if verteces have capacity as well as edges, simply devide each vertex to two vertex with an edge between them
// equal to capacity of the vertex


int s, t, f, mf; //s is start node, t is destination, fill s and t in main. mf will hold the max flow.
vvi graph, res;//graph is adjList fill it in main, res is a n * n 2D vec with capacity of each edge.
vi p;

void augment(int v, int minEdge) {
    if(v == s) {
        f = minEdge; return;
    }
    else if(p[v] != -1) {
        augment(p[v], min(minEdge, res[p[v]][v]));
        res[p[v]][v] -= f; res[v][p[v]] += f;
    }
}

void edmonsKarp(int n) { // n is the graph size. answer is in mf after calling this method.
    mf = 0;
    while(1) {
        f = 0;
        vector<bool> vis(n, false); vis[s] = true;
        p.clear(); p.resize(n, -1);
        queue<int> queue1; queue1.push(s);
        while(!queue1.empty()) {
            int u = queue1.front(); queue1.pop();
            if(u == t) break;
            for(auto &e : graph[u]) {
                if(res[u][e] > 0 && !vis[e]) vis[e] = true, queue1.push(e), p[e] = u;
            }
        }
        augment(t, inf);
        if(f == 0) break;
        mf += f;
    }
}
