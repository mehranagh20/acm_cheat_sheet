ll maxSubarrayXOR(vector<ll> set) {
    ll index = 0, n = set.size();
    for (int i = LONG_BIT - 1; i >= 0; i--) {
        ll maxInd = index, maxEle = LONG_LONG_MIN;
        for (int j = index; j < n; j++) {
            if ((set[j] & (1LL << i)) != 0
                && set[j] > maxEle)
                maxEle = set[j], maxInd = j;
        }
        if (maxEle == LONG_LONG_MIN)
            continue;
        swap(set[index], set[maxInd]);
        maxInd = index;
        for (int j = 0; j < n; j++) {
            if (j != maxInd &&
                (set[j] & (1LL << i)) != 0)
                set[j] = set[j] ^ set[maxInd];
        }
        index++;
    }
    ll res = 0;
    for (int i = 0; i < n; i++)
        res ^= set[i];
    return res;
}
