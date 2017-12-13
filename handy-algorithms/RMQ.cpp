struct RMQ { // construct rmq in n * log(n), takes n * log(n) space. query in O(1).
    int len;
    vvi rmq;
    vvi ind;

    void init(vi arr) { // call this method with your desired array.
        len = arr.size();
        int lg = log(len) / log(2) + 20;
        rmq.assign(len + 10, vi(lg, 0));
        ind.assign(len + 10, vi(lg, 0));
        for (int i = 0; i < len; i++)
            rmq[i][0] = arr[i], ind[i][0] = i;
        for (int j = 1; j < lg; j++)
            for (int i = 0; i < len; i++) {
                if (i + (1 << j) > len)
                    break;
                if(rmq[i][j - 1] < rmq[i + (1 << (j - 1))][j - 1])
                    rmq[i][j] = rmq[i][j - 1], ind[i][j] = ind[i][j - 1];
                else
                    rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1], ind[i][j] = ind[i + (1 << (j - 1))][j - 1];
            }
    }

    ii range_minimum_query(int l, int r) { // it is 0 base, manage so that 'l' and 'r' are in range!, first element is the min element, second element is index of min element in the range.
        if (l > r)
            swap(l, r);

        int interval_len = r - l;

        int first_half = 1;
        while ((1 << first_half) <= interval_len)
            first_half++;
        first_half--;

        int second_half = r - (1 << first_half) + 1;
        if(rmq[l][first_half] < rmq[second_half][first_half]) return ii(rmq[l][first_half], ind[l][first_half]);
        else return ii(rmq[second_half][first_half], ind[second_half][first_half]);

    }
};
