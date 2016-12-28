// Complete Search:
// Use list<int> or vector<int> to simulate the process

// Special Case k = 2 (skipping rule = 2)
// if n = 1b1b2b3..bn (in binary format) then the surviver is b1b2b3..bn1

// General Case:
// n = number of men
// k = skipping step
// Output: 0-based index of the surviver (add 1 if you want it to become 1-based)
int josephus(int n, int k) {
  if (n == 1)
    return 0;
  return (josephus(n - 1, k) + k) % n;
}
