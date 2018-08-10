const int SQRT_MX = 20000; // sqrt of maximum number of n
bool bl[SQRT_MX + 10]; // use as cross-by table
ll primes[SQRT_MX + 10]; // stores primes till SQRT_MX

// cal this method with n to get primes from 2 to n
void blockSieve(ll n) { // same complexity as original sieve, memory complexity is O(sqrt(n) * 2) instead of O(n)
    ll cnt = 0;
    memset(bl, false, sizeof bl);
    for (int i = 2; i <= SQRT_MX; ++i)
        if (!bl[i]) {
            primes[cnt++] = i;
            if (i * 1ll * i <= SQRT_MX)
                for (int j = i * i; j <= SQRT_MX; j += i)
                    bl[j] = true;
        }

    for (int k = 0, maxk = n / SQRT_MX; k <= maxk; ++k) {
        memset(bl, false, sizeof bl);
        int start = k * SQRT_MX;
        for (int i = 0; i < cnt; ++i) {
            int start_idx = (start + primes[i] - 1) / primes[i];
            int j = max(start_idx, 2) * primes[i] - start;
            for (; j < SQRT_MX; j += primes[i])
                bl[j] = true;
        }
        if (k == 0) bl[0] = bl[1] = true;
        for (int i = 0; i < SQRT_MX && start + i <= n; ++i)
            if (!bl[i]) {
                // i + start is a prime, you can manipulate it :)
            }
    }
}
