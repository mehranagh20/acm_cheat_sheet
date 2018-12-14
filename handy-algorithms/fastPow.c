/**
 * NOTE:
 * n^e mod m = n^(φ(m)+(e mod φ(m))) mod m.
 */


ll pw(ll a, ll b) {
    if (b == 0) {
        return 1;
    }

    ll v = pw(a, b / 2);
    v = (v * v) % MOD;

    if (b & 1) {
        v = (v * a) % MOD;
    }

    return v;
}
