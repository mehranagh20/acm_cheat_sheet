vi arr, t, lazy; // arr is numbers to build seg tree with, if its size is 'n' then t and lazy size should be 4 * n (2 * n)

void build(int node, int a, int b){ // call build(1, 0, n - 1) for n elements
    if(a > b) return;
    if (a == b){
        t[node] = arr[a]; return;      
    }

    build(node*2, a, (a+b)/2);
    build(node*2+1,(a+b)/2+1,b);

    t[node] = t[node * 2] + t[node * 2+1]; // update here in case of change of operation, for example min
}

ull query(int node, int a, int b, int i, int j){ // call query(1, 0, n - 1, i, j) to get query of i..j for seg tree of n elements
    if(a>b || a>j || b<i) return 0;
    if (lazy[node] !=0 ){
        t[node]+=lazy[node]*(b-a+1); // it is possible to update the tree in ways other that increasing a range.
        // for example it is possible to change all the elements of a range to a number, for example all numbers in range of i..j to 11
        // just underestand the way lazy works and change lazy arr value and interaction between lazy and real tree array, like t[node] = lazy[node] * (b - a + 1)
        if (a!=b){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node]=0;
    }

    if (a >= i && b <= j) return t[node];

    ull q1=query(node*2, a, (a+b)/2, i, j);
    ull q2=query(node*2+1, (a+b)/2+1, b, i, j);

    return q1 + q2; // update here in case of change of operation, for example min
}

void update(int node, int a, int b, int i, int j, int inc){
    if(a > b) return;
    if (lazy[node] !=0) {
        t[node] += lazy[node] * (b-a+1);
        if (a!=b) {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
        }
        lazy[node] = 0;
    }
    if(a>b || a>j || b<i) return;

    if (a >= i && b <= j){
        t[node]+=inc*(b-a+1);
        if (a!=b){
            lazy[node*2]+=inc;
            lazy[node*2+1]+=inc;
        }
        return;
    }

    update(node*2, a, (a+b)/2, i, j, inc);
    update(node*2+1, (a+b)/2+1, b,i, j, inc);
    t[node] = t[node*2] + t[node*2+1]; // update here in case of change of operation, for example min
}

// in main, assign t, arr, lazy then build the tree like specified above
