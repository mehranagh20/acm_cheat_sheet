# Combinatorics

### Fibonacci numbers
`fib(0) = 0` and `fib(1) = 1`  
`fib(n) = fib(n - 2) + fib(n - 1)` for `n > 2`

`0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...`

* O(n) Algorithm using recursion

```cpp
vector<long long> fibseq;

ll fib(int n) {
	if (n < fibseq.size())
		return fibseq[n];
	if (n < 2)
		return n;
	fibseq.push_back(fib(n - 2) + fib(n - 1));
	return fibseq[n];
}
```

**QFibonacci**

* O(lg n) using matrix
* `qfib(n).first` is equal to `fib(n)`
* `ii` refers to `pair<long long, long long>`

```cpp
ii qfib(ll n) {
	if (n == 0)
		return ii(0, 1);
	ii fib = qfib(n / 2);
	ll c = fib.first * ((((fib.second * 2) % mod) - fib.first + mod) % mod);
	c %= mod;
	ll d = (fib.first * fib.first) % mod + (fib.second * fib.second) % mod;
	d %= mod;
	if (n % 2 == 0)
		return ii(c, d);
	return ii(d, (c + d) % mod);
}
```

**Binet's formula**

* O(1)
* Not precise for `n > 75` where `len(fib(n)) ~ 15`

```cpp
double phi = (1 + sqrt(5)) / 2;

double binets_fib(int n) {
    double binets_fib(int n) {
    return (pow(phi, n) - pow(-phi, -n)) / sqrt(5);
}

// round to binets_fib to nearest integer
// (long long)(binets_fib(n) + 0.5)
```

### Binomial Coefficients

**Recursive formula:**

`C(n, 0) = C(n, n) = 1`  
`C(n, k) = C(n - 1, k - 1) + C(n - 1, k)` for `n > k > 0`

**Pascal's Triangle:** This triangle uses above formula

```
n=0           1
n=1         1   1
n=2       1   2   1
n=3     1   3   3   1
         \/  \/   \/
n=4   1  4   6    4   1
```

### Catalan Numbers

`1, 1, 2, 5, 14, 42, 132, 429, ...`

**General formula:**

`cat(0) = 1`  
`cat(n) = C(2n, n) / (n + 1)`

**Recursive formula:**

`cat(n) = ((2n * (2n - 1)) / (n + 1) * n) * cat(n - 1)`

**Properties:**
* `cat(n)` counts the number of distinct binary trees with
`n` vertices, e.g.:

```
n = 3 -> cat(3) = 5

    *   *   *   *   *
   /   /   / \    \   \
  *   *   *   *    *   *
 /     \          /     \
*       *        *       *
```

* `cat(n)` counts the number of expressions containing n pairs of parentheses which are correctly matched, e.g. for `n = 3`, we have: `()()()`, `()(())`, `(())()`, `((()))`, and `(()())`.

* `cat(n)` counts the number of different ways `n + 1` factors can be completely parenthe-sized, e.g. for `n = 3` and `3 + 1 = 4` factors: `{a, b, c, d}` , we have: `(ab)(cd)`, `a(b(cd))`, `((ab)c)d`, `(a(bc))(d)`, and `a((bc)d)`.

* `cat(n)` counts the number of ways a convex polygon of `n + 2` sides can be triangulated.

* `cat(n)` counts the number of monotonic paths along the edges of an `n × n` grid, which do not pass above the diagonal. A monotonic path is one which starts in the lower left corner, finishes in the upper right corner, and consists entirely of edges pointing rightwards or upwards.
