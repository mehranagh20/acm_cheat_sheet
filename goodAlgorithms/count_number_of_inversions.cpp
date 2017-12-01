// counting inversion algorithm, runs in O(n * log(n))
// inversion in an array is of form ....x......y..... if x > y.
//
// it is possible to compute the inversion between two arrays
// example of inversion of two arrays:
// ...x...y... first array
// ..y........x... second array
// let a and b be the arrays.
// fill nums to hold for each index of 'b' the index of number in that index of 'b' in 'a'
// foreach element in a: tmp[a[i]] = i
// foreach element in b: nums[i] = tmp[b[i]]

vi nums; // holds the actual numbers
vi tmp; // temporary array, just resize it with size of nums array.

ll merge_count(int a, int b) {
    ll k = a, now = 0;
    ll i = a, j = (a + b) / 2 + 1, mid = (a + b) / 2;
    while(i <= (a + b) / 2 && j <= b) {
        if(nums[i] < nums[j]) tmp[k] = nums[i++];
        else tmp[k] = nums[j++], now += mid - i + 1;
        k++;
    }
    while(i <= (a + b) / 2) { tmp[k++] = nums[i++];}
    while(j <= b) { tmp[k++] = nums[j++];}

    for(int i = a; i <= b; i++) nums[i] = tmp[i];
    return now;
}

ll count(int a, int b) { // call this methid with 0, nums.size() - 1, for getting inversions of whole array.
    if(b - a + 1 <= 1) return 0;
    ll x = count(a, (a + b) / 2) + count((a + b) / 2 + 1, b);
    return x + merge_count(a, b);
}
