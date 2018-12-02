int zero_matrix(vvi a) { // O(N * M)
    int n = a.size(), m = a[0].size(), ans = 0;
    vi d(m, -1), d1(m), d2(m), st;

    forn(i, n) {
        forn(j, m) if (a[i][j] == 1) d[j] = i;

        forn(j, m) {
            while (st.size() && d[st.back()] <= d[j]) st.pop_back();
            d1[j] = st.empty() ? -1 : st.back();
            st.push_back(j);
        }
        st.clear();

        for (int j = m - 1; j >= 0; --j) {
            while (st.size() && d[st.back()] <= d[j]) st.pop_back();
            d2[j] = st.empty() ? m : st.back();
            st.push_back(j);
        }
        st.clear();

        forn(j, m) ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1)); 
    }
    return ans;
}
