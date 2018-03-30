ll n = 3, MOD = 1e9 + 7; // change n and MOD to meet your requirements

vvi matMul(vvi &a, vvi &b) {
    vvi c(n, vi(n, 0));
    int k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (k = 0; k < n; k++) {
                c[i][j] += (a[i][k] % MOD) * (b[k][j] % MOD);
                c[i][j] %= MOD;
            }
    return c;
}

vvi matPow(vvi base, ll p) {
    vvi ans(n, vi(n, 0)); int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            ans[i][j] = (i == j);
    while (p) {
        if (p & 1)
            ans = matMul(ans, base);
        base = matMul(base, base);
        p >>= 1;
    }
    return ans;
}

[[1 , 1] , [1 , 0]] ** n = [[fib(n+1) , fib(n)], [fib(n) , fib(n-1)]] 
// FIBONACCI FORMULA
