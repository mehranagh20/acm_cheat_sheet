// The prefix function is defined as an array of length n, where π[i] is the length of the
// longest proper prefix of the substring s[0…i] which is also a suffix of this substring.

vi prefix_function(string s) {
    int n = s.size();
    vi pi(n);
    forn (int i = 1; i < n; i++) {
        auto j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
