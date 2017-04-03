// O(nlogn)
string T; // the input string
int n; // n is size of input string
vi RA, tempRA, SA, tempSA, c; // RA is rank array, SA is suffix array, c must have max(300, n) elements.

void countingSort(int k) {
    int i, sum, maxi = max(300, n);
    fill(c.begin(), c.end(), 0);
    for (i = 0; i < n; i++)
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++)
        swap(sum, c[i]), sum += c[i];
    for (i = 0; i < n; i++)
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    SA = tempSA;
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i;
    for (k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++)
            tempRA[SA[i]] =
                    (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        RA = tempRA;
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

// resize the arrays in main, set n
