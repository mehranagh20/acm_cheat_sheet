// to check an undirected graph to see if it is eulerian: check if all its vertices have even degrees then it is eulerian.
// an undirected graph has an euler path if all except two vertices have even degrees, start from one odd and finish in another one.


// before running below alg, make sure the given graph is an eulerian graph --> vertices have even degrees.
// graph is adjacency list where the second attrubute in edge info is 1 (this edge can still be used)
// or 0 (this edge can no longer be used).

list<int> cyc; // holds the path (tour) after running alg.

void EulerTour(list<int>::iterator i, int u) {
    for (int j = 0; j < (int)graph[u].size(); j++) {
        ii &v = graph[u][j];
        if (v.second) {
            v.second = 0;
            for (int k = 0; k < (int)graph[v.first].size(); k++) {
                ii &uu = graph[v.first][k];
                if (uu.first == u && uu.second) {
                    uu.second = 0;
                    break;
                }
            }
            EulerTour(cyc.insert(i, u), v.first);
        }
    }
}

// in the main
cyc.clear();
EulerTour(cyc.begin, start); // start is any vertices.
