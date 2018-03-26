// z function returns an array of size |s| which i'th number shows size of longest prefix of t starting from this index of s
// O(|s| + |t|)

// t is the pattern you are looking for in s
vi zf(string s, string t) {
    int n = s.size(), m = t.size();
    s = t + '#' + s;
    vi z(n + m + 1);
    int l = 0, r = 1;
    for (int i = 1; i <= n + m; i++) {
        if (i < r) z[i] = min(z[i - l], r - i);
        while (i + z[i] <= n + m && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > r)
            tie(l, r) = ii(i, i + z[i]);
    }
    vi ret_z(n);
    forn(i, n) ret_z[i] = z[i + m + 1];
    return ret_z;
}
