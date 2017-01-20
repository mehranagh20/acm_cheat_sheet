# Number Theory

### Prime Numbers

**Sieve of Eratosthenes**: to generate list of prime numbers
* O(n log log n): `n = 1e7`
**Prime checker**
* O(1) for `n <= sieve_size` and O(sqrt(n) / ln sqrt(n)) for bigger `n`s.


```cpp
#include <bitset>

ll sieve_size;
bitset<10000010> bs; // 10^7 should be enough for most cases
vi primes;

 // create list of primes in [0..upperbound]
void sieve(ll upperbound) {
    sieve_size = upperbound + 1; // add 1 to include upperbound
    bs.set(); // set all bits to 1
    bs[0] = bs[1] = 0; // except index 0 and 1
    for (ll i = 2; i <= sieve_size; i++)
        if (bs[i]) {
        // cross out multiples of i starting from i * i!
        for (ll j = i * i; j <= sieve_size; j += i) bs[j] = 0;
        primes.push_back(i);
    }
}

bool isPrime(ll n) {
    if (n <= sieve_size) return bs[n];
    for (int i = 0; i < primes.size(); i++)
        if (n % primes[i] == 0) return false;
    return true;
} // note: only work for n <= (last prime in vi "primes")^2

// inside main()
sieve(10000000); // can go up to 10^7 (need few seconds)
```

### GCD and LCM

* O(log10 n): `n = max(a, b)`

```cpp
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return a * (b / gcd(a, b));
}
```

### Factorial

* O(n)

```cpp
// ll can hold up to fact(20); for beyond use Java BigInteger
ll fact(int n) {
    return n == 0 ? 1 : n * fact(n - 1);
}
```

### Prime-Power Factorization

* O(sqrt(n) / ln sqrt(n))

```cpp
// needs sieve of eratosthenes
vi primeFactors(ll n) {
    vi factors;
    ll PF_idx = 0, PF = primes[PF_idx];
    while (PF * PF <= n) {
        while (n % PF == 0) {
            n /= PF;
            factors.push_back(PF);
        }  
        PF = primes[++PF_idx];
    }
    if (n != 1) factors.push_back(n); // special case if n is a prime
    return factors;
}

// inside int main(), assuming sieve(1000000) has been called before
vi r = primeFactors(2147483647);
```

### Functions involving prime numbers

* `numPF(n)`: Count the number of prime factors of `n`

```cpp
ll numPF(ll n) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (PF * PF <= n) {
        while (n % PF == 0) {
            n /= PF;
            ans++;
        }
        PF = primes[++PF_idx];
    }
    if (n != 1) ans++;
    return ans;
}
```

* `numDiffPF(n)`: Count the number of *different* prime factors of `n`

```cpp
ll numDiffPF(ll n) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (PF * PF <= n) {
        int power = 0
        while (n % PF == 0) {
            n /= PF;
            power++;
        }
        if (power)
            ans++;
        PF = primes[++PF_idx];
    }
    if (n != 1) ans++;
    return ans;
}
```

* `numDiv(n)`: Count the number of *divisors* of `n`

```cpp
ll numDiv(ll n) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1;
    while (PF * PF <= n) {
        ll power = 0;
        while (n % PF == 0) {
            n /= PF;
            power++;
        }
        ans *= power + 1;
        PF = primes[++PF_idx];
    }
    if (n != 1) ans *= 2; // last factor has pow = 1, we add 1 to it
    return ans;
}
```

* `sumDiv(n)`: Sum of divisors of `n`

```cpp
ll sumDiv(ll n) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1;
    while (PF * PF <= n) {
        ll power = 0;
        while (n % PF == 0) {
            n /= PF;
            power++;
        }
        ans *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);
        PF = primes[++PF_idx];
    }
    if (n != 1) ans *= ((ll)pow((double)n, 2.0) - 1) / (n - 1);  // last
    return ans;
}
```

* `EulerPhi(n)`: Count the number of positive integers < `n` that are relatively prime to `n`

The formula is: `phi(n) = n * PI (1 - 1/PF) for PF = prime factors of n`

```cpp
ll EulerPhi(ll n) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = n;
    while (PF * PF <= n) {
        if (n % PF == 0) ans -= ans / PF;
        while (n % PF == 0) n /= PF;
        PF = primes[++PF_idx];
    }
    if (n != 1) ans -= ans / n;
    return ans;
}
```

### Modified Sieve

Used when there are many numbers to determine `numDiffPF` for them

```cpp
vi numDiffPF(MAX_N, 0);

for (int i = 2; i < MAX_N; i++)
    if (numDiffPF[i] == 0) // i is a prime number
        for (int j = i; j < MAX_N; j += i)
            numDiffPF[j]++; // increase the values of multiples of
```

### Extended Euclid: Solving Linear Diophantine Equation

Suppose we have `ax + by = c` and `d = gcd(a, b)`.  
If `d | c` is not true then there is no integral solutions.  
Otherwise the first solution `(x0, y0)` can be found using **Extended Euclid**.
Then other solutions can be derived from `x = x0 + (b/d)n` and `y = y0 - (a/d)n`.

```cpp
// store x, y, and d as global variables
void extendedEuclid(int a, int b) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    } // base case
    extendedEuclid(b, a % b); // similar as the original gcd
    int x1 = y;
    int y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}
```
