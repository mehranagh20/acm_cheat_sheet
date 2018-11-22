// Linear sieve, change it to use bitset instead
// runs in O(n) since it crosses the composite numbers exactly once
std::vector <int> prime;
bool is_composite[MAXN];

void sieve (int n) {
	std::fill (is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

=======
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
long long gcd(long long a, long long b) {
    while (a > 0 && b > 0) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
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
long long gcd(long long a, long long b) {
    while (a > 0 && b > 0) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}
