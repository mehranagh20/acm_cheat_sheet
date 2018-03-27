// this technique converts path queries on tree to array range query, possible to run tricks like Mo on this array

int cnt = 0;
vi l, r, oc;
void dfss(int i, int p) { // special dfs that saves fist and last time counter of seeing a node in l and r and order in 'oc'
    oc.push_back(i);
    l[i] = cnt++;
    for(auto &e: children[i]) if(e != p)
            dfss(e, i);
    r[i] = cnt++;
    oc.push_back(i);
}

struct rng {
    int l, r, i, lc;
};
vector<rng> rngs;
vi occ;

// this function is an example of answering to queries
vi vis;
int ans = 0;
void check(int a) {
    if(vis[a]) occ[w[a]]--, ans -= (occ[w[a]] == 0);
    else occ[w[a]]++, ans += (occ[w[a]] == 1);
    vis[a] ^= 1;
}

int main() {
    // get graph and build lcs of it with RMQ in n * log(n)
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        children[a - 1].push_back(b - 1), children[b - 1].push_back(a - 1);
    }

    // run special dfs for constructing range array
    l.assign(n + 10, 0), r.assign(n + 10, 0);
    dfss(0, -1);
    s = sqrt(oc.size()) + 1;

    for(int i = 0; i < q; i++) {
        // get path queries and convert them to l and r in array we just constructed with special dfs with the help of lcs
        int a, b; cin >> a >> b;
        a--, b--;
        rng rn;
        if(H[a] >= H[b]) swap(a, b);

        if(lcs(a, b) == a) rn.l = l[a], rn.r = l[b];
        else rn.l = r[a], rn.r = l[b];
        rn.i = i;
        rn.lc = lcs(a, b);
        rngs.push_back(rn); // holds all the range queries, you may answer them on the fly, but be careful that nodes appear two times in array
    }

    sort(rngs.begin(), rngs.end(), cmp); // or you may just use other tricks like Mo's algorithm
    for(auto &e: rngs) {
        // answer to queries
        // if a node is appeared two times in the range e.l and e.r then we do not pass it and we ignore it. maybe siding window technique
        // to overcome this issue
        // for example checkout check function above
        while(cl < e.l) check(oc[cl]), cl++;
        while(cl > e.l) cl--, check(oc[cl]);
        while(cr < e.r) cr++, check(oc[cr]);
        while(cr > e.r) check(oc[cr]), cr--;
        // ...
    }
}


