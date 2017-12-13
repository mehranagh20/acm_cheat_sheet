struct RMQ { // construct rmq in n * log(n), takes n * log(n) space. query in O(1).
    int len;
    vvi rmq;

    void init(vi arr) { // call this method with your desired array.
        len = arr.size();
        int lg = log(len) / log(2) + 20;
        rmq.assign(len + 10, vi(lg, 0));
        for (int i = 0; i < len; i++)
            rmq[i][0] = arr[i];
        for (int j = 1; j < lg; j++)
            for (int i = 0; i < len; i++) {
                if (i + (1 << j) > len)
                    break;
                rmq[i][j] = rmq[i][j - 1];
                rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j-1]);
            }
    }

    int range_minimum_query(int l, int r) { // it is 0 base, manage so that 'l' and 'r' are in range!
        if (l > r)
            swap(l, r);

        int interval_len = r - l;

        int first_half = 1;
        while ((1 << first_half) <= interval_len)
            first_half++;
        first_half--;

        int second_half = r - (1 << first_half) + 1;
        return min(rmq[l][first_half], rmq[second_half][first_half]);
    }
};