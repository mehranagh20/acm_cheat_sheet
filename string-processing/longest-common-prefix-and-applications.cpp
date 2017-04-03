// O(n)
// finding common prefix between each subsequence sufix of a string in suffix array.
vi Phi, PLCP, LCP; // LCP is the longest common prefix, resize each with size of string before calling

// needs suffix array before running.
void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1];
    for (i = L = 0; i < n; i++) {
        if (Phi[i] == -1) { PLCP[i] = 0; continue; }
        while (T[i + L] == T[Phi[i] + L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}

// Apclications.

// 1. Finding the Longest Repeated Substring
// longest repeated substring of a string is the maximum number in longest common prefix array.

// 2.Finding the Longest Common Substring
// suppose we have just two strings:
// append each one with a low assci char then join them together --> A = abc and B = cgf
// A --> abc# and B --> cgf$ --> abc#cgf$
// now construct suffix array and LCP.
// then longest common substring is the maximum number in the LCP array where for example
// sufix i and i - 1 belong to different strings.
// if suffix i belong to A then SA[i] < length of A.
// this is extendable to more than two strings.

// ***** sometimes there are duplicate answers with this longest common substring 
// algorithm, so check string you are printing with the prevoius one, if same do not print.

