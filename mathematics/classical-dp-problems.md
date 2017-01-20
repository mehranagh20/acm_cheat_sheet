# Classical Dynamic Programming Problems

### 1. Max 1D Range Sum

**Kadane's Algorithm:**

* O(n)

```cpp
int kadane(int a[], int n) { // n is size of array a
    int sum, ans = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
    }
    return ans;
}
```

### 2. Max 2D Range Sum
**Using Kadane's Algorithm Over 2D**: `n` and `m` are dimensions of array `a`.
* O(n^3)

```cpp
for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
// input a[i][j] if needed
if (j > 0) a[i][j] += a[i][j - 1]; // only add columns of this row i
}

maxSubRect = -inf; // the lowest possible number
for (int l = 0; l < n; l++) for (int r = l; r < ; r++) {
    subRect = 0;
    for (int row = 0; row < n; row++) {
        // Max 1D Range Sum on columns of this row i
        if (l > 0) subRect += a[row][r] - a[row][l - 1];
        else       subRect += a[row][r];
        // Kadane’s algorithm on rows
        if (subRect < 0) subRect = 0;
        maxSubRect = max(maxSubRect, subRect);
    }
}
```

### 3. Longest Increasing Subsequence (LIS)

* O(n log k): `n` is the size of the array and `k` is the size of the LIS

```cpp
vi seq;
// input seq
vi l(seq.size(), 0), l_index(seq.size(), 0), suc(seq.size(), -1);
int lis = 0, lis_end = 0;
for (int i = 0; i < seq.size(); i++) {
    int pos = lower_bound(l.begin(), l.begin() + lis, seq[i]) - l.begin();
    l[pos] = seq[i];
    l_index[pos] = i;
    suc[i] = pos ? l_index[pos - 1] : -1;
    if (pos + 1 > lis) {
        lis = pos + 1;
        lis_end = i;
    }
}
// the lis length is in lis
```

* O(n^2)

```cpp
vi seq;
// input seq
vi lis(seq.size(), 1), suc(seq.size(), -1);
for (int i = 1; i < n; i++)
	for (int j = 0; j < i; j++)
		if (seq[i] > seq[j] && lis[i] <= lis[j]) {
			lis[i] = lis[j] + 1;
            suc[i] = j;
        }
// the answer is in largest value of lis
```

**Reconstruct the LIS**: using a stack

```cpp
stack<int> s;
int i;
for (i = lis_end; suc[i] >= 0; i = suc[i])
    s.push(seq[i]);

cout << seq[i];
while (!s.empty()) {
    cout << ', ' << s.top();
    s.pop();
}
cout << endl;
```

### 4. 0-1 Knapsack (Subset Sum)

* Both versions are O(nW): `n` is the number of items and `W` is the size of knapsack

**Top-Down version (faster then Bottom-Up):**

```cpp
// globals:
int n; // number of items
vi W, V;
// W array holds weights of items
// V array holds values of items
vvi memo;
// memo array is used to memorize states

// value function returns the most value which holds into w from id to end
int value(int id, int w) {
    if (id == n || w == 0) return 0;
    if (memo[id][w] != -1) return memo[id][w];
    if (W[id] > w)         return memo[id][w] = value(id + 1, w);
    return memo[id][w] = max(value(id + 1, w), V[id] + value(id + 1, w - W[id]));
}

// inside main():
W.resize(n + 1, 0);
V.resize(n + 1, 0);
memo.resize(n + 1, vi(MW, 0));

// the answer is in value(0, MW); MW = size of knapsack
```

**Bottom-UP version:**

```cpp
int n; // number of items
// input n

vi W(n + 1, 0), V(n + 1, 0);
// W holds weights of items
// V holds values of items

// input W and V

vvi dp(n + 1, vi(MW, 0)); // dp is used to memorize the states
for (i = 0; i <= N;  i++) dp[i][0] = 0;
for (w = 0; w <= MW; w++) dp[0][w] = 0;

for (i = 1; i <= N; i++)
for (w = 1; w <= MW; w++) {
    if (W[i] > w) dp[i][w] = dp[i - 1][w];
    else          dp[i][w] = max(dp[i - 1][w], V[i] + dp[i - 1][w - W[i]]);
}
// the answer is in dp[n][MW]
```

### 5. Coin Change (CC)

* O(nV): `n` is the number of coin types and `V` is amount of money

**General version: Find the minimum number of coins needed**

```cpp
vi coinValue(n, 0), // holds the value of coins
   memo(V + 1, inf); // used to memorize the states

int change(int value) {
    if (value == 0) return 0;
    if (value < 0) return inf;
    if (memo[value] < inf) return memo[value];
    for (int i = 0; i < n; i++)
        memo[value] = min(memo[value], change(value - coinValue[i]))
    return memo[value] += 1;
}

// the answer is in change(V)
```

**Variant: Find the number of possible ways to get value V**

```cpp
// globals:
int n; // number of coin types
vi coinValue; // holds the value of coins
vvi memo; // used to memorize the states

int ways(int type, int value) {
    if (value == 0)              return 1;
    if (value < 0 || type == n)  return 0;
    if (memo[type][value] != -1) return memo[type][value];
    return memo[type][value] = ways(type + 1, value) + ways(type, value - coinValue[type]);
}

// inside main():
int V; // the value of money
// input V

// coinValue.clear(); if multiple testcases
coinValue.resize(n, 0);

// input coinValue

// memo.clear(); if multiple testcases
memo.resize(n, vi(V + 1, -1));

// the answer is in ways(0, V); V is the value of money
```

### 6. Traveling Salesman Problem

* O(n^2 * 2^n): feasible only with n <= 16

```cpp
int start; // initialize before function

int tsp(int pos, int bitmask) { // bitmask stores the visited coordinates
    if (bitmask == (1 << (n + 1)) - 1)
    return dist[pos][start]; // return trip to close the loop
    if (memo[pos][bitmask] != -1)
    return memo[pos][bitmask];

    int ans = inf;
    for (int nxt = 0; nxt <= n; nxt++) // O(n) here
    if (nxt != pos && !(bitmask & (1 << nxt))) // if coordinate nxt is not visited yet
        ans = min(ans, dist[pos][nxt] + tsp(nxt, bitmask | (1 << nxt)));
    return memo[pos][bitmask] = ans;
}

// the answer is in tsp(start, 1 << start); start is the index of starting node
```
