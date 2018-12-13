class UFDS {
public:
    vi p, rank, setSizes;
    int numSets;

    UFDS(int n): numSets(n), rank(n, 0), p(n, 0), setSizes(n, 1) {
        forn(i, n) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : p[i] = findSet(p[i]); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) {
                setSizes[x] += setSizes[y]; p[y] = x;
            }
            else {
                setSizes[y] += setSizes[x]; p[x] = y;
                if (rank[x] == rank[y]) rank[y]++;
            }
            numSets--;
        }
    }
    int setSize(int i) { return setSizes[findSet(i)]; }
};
