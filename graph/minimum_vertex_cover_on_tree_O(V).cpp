// minimum vertex cover is the problem of finding minimum number of vertices such that each edge of tree is incident to at least one vertex of selected set.

// answer is in min(MVC(root, false), MVC(root, true))
int MVC(int v, int flag) { // Minimum Vertex Cover
    int ans = 0;
    if (memo[v][flag] != -1) 
        return memo[v][flag]; // reserve memo in main, memo.resize(n, vi(2, -1)), where n is number of vertices.
    else if (leaf[v]) // leaf[v] is true if v is a leaf, false otherwise
        ans = flag;
    else if (flag == 0) { // if v is not taken, we must take its children
        // Note: ‘Children’ is an Adjacency List that contains the directed version of the tree
        // (parent points to its children; but the children does not point to parents)
        ans = 0;
        for (int j = 0; j < (int)Children[v].size(); j++)
            ans += MVC(Children[v][j], 1);
    }
    else if (flag == 1) {
        ans = 1;
        for (int j = 0; j < (int)Children[v].size(); j++)
            ans += min(MVC(Children.[v][j], 1), MVC(Children[v][j], 0));
    }
    return memo[v][flag] = ans;
}
