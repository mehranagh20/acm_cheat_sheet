int arr[N]; // contains numbers for building segTree
int tree[MAX]; // tree representation. MAX = 4 * n
int lazy[MAX]; // array for labeling to update

void build_tree(int node, int a, int b) {
  	if(a > b) return; // Out of range
  	
  	if(a == b) { // Leaf node
    		tree[node] = arr[a]; // Init value
		return;
	}
	
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	
	tree[node] = max(tree[node*2], tree[node*2+1]); // to change max seg_tree to for example sum query
        // change max operator to + operator tree[node] = tree[node*2] + tree[node*2+1];
}

 // Increment elements within range [i, j] with value value
void update_tree(int node, int a, int b, int i, int j, int value) { // update will add value to range, to set range to sth
    // you should change this.
  
  	if(lazy[node] != 0) { // This node needs to be updated
   		tree[node] += lazy[node]; // Update it

		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
    		lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}

   		lazy[node] = 0; // Reset it
  	}
  
	if(a > b || a > j || b < i) // Current segment is not within range [i, j]
		return;
    
  	if(a >= i && b <= j) { // Segment is fully within range
    		tree[node] += value;

		if(a != b) { // Not leaf node
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}

    		return;
	}

	update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

	tree[node] = max(tree[node*2], tree[node*2+1]); // to change max seg_tree you must change max operator
}

 // Query tree to get max element value within range [i, j]
int query_tree(int node, int a, int b, int i, int j) {
	
	if(a > b || a > j || b < i) return -inf; // Out of range

	if(lazy[node] != 0) { // This node needs to be updated
		tree[node] += lazy[node]; // Update it

		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}

		lazy[node] = 0; // Reset it
	}

	if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node];

	int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
	int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

	int res = max(q1, q2); // final result, to change max seg_tree you must change max operator
	
	return res;
}

int main() {
	for(int i = 0; i < N; i++) arr[i] = 1;

	build_tree(1, 0, N-1);

	memset(lazy, 0, sizeof lazy);

	update_tree(1, 0, N-1, 0, 6, 5); // Increment range [0, 6] by 5. here 0, N-1 represent the current range.
	update_tree(1, 0, N-1, 7, 10, 12); // Incremenet range [7, 10] by 12. here 0, N-1 represent the current range.
	update_tree(1, 0, N-1, 10, N-1, 100); // Increment range [10, N-1] by 100. here 0, N-1 represent the current range.

	cout << query_tree(1, 0, N-1, 0, N-1) << endl; // Get max element in range [0, N-1]
}
