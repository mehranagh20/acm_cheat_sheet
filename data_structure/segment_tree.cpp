class SegmentTree { 
private:
    vi st, A;
    int n;

    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) { 
        if (L == R)
            st[p] = L;
        else { // recursively compute the values
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R
            );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }

    int rmq(int p, int L, int R, int i, int j) { // O(log n)
        if (i > R || j < L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p]; // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);
        if (p1 == -1) return p2; // if we try to access segment outside query
        if (p2 == -1) return p1; 
        return (A[p1] <= A[p2]) ? p1 : p2; // as in build routine
    }

public:
    SegmentTree(const vi &_A) {
        A = _A;
        n = (int) A.size();
        st.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // overloading
};

// in the main
//int main() {
	// example
    //int arr[] = {18, 17, 13, 19, 15, 11, 20};
    //vi A(arr, arr + 7);
    //SegmentTree st(A);
//}
