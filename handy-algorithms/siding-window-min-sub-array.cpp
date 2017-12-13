void SlidingWindow(int A[], int n, int K) {
// ii---or pair<int, int>---represents the pair (A[i], i)
    deque<ii> window; // we maintain ‘window’ to be sorted in ascending order
    for (int i = 0; i < n; i++) {
// this is O(n)
        while (!window.empty() && window.back().first >= A[i])
            window.pop_back();
// this to keep ‘window’ always sorted
        window.push_back(ii(A[i], i));
// use the second field to see if this is part of the current window
        while (window.front().second <= i - K)
// lazy deletion
            window.pop_front();
        if (i + 1 >= K)
// from the first window of length K onwards
            printf("%d\n", window.front().first); // the answer for this window
    } }