// floyd warshal alg is used for findign shortest path between any two verteces, feasible for V <= 400.


// inside int main()
// let p be a 2D parent matrix, where p[i][j] is the last vertex before j
// on a shortest path from i to j, i.e. i -> ... -> p[i][j] -> j

for (int i = 0; i < n; i++)
   for (int j = 0; j < n; j++)
        p[i][j] = i; // initialize the parent matrix

for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) // this time, we need to use if statement
            if (AdjMat[i][k] + AdjMat[k][j] < AdjMat[i][j]) {
                AdjMat[i][j] = AdjMat[i][k] + AdjMat[k][j];
                p[i][j] = p[k][j];
            }



// this func is used to print the shortest path using p vector after running the alg.
void printPath(int i, int j) {
    if (i != j) printPath(i, p[i][j]);
    printf(" %d", j);
}

// VARIANTS :


// 1. findig circle (cheapest circle or detecting negative circle):
// just set AdjMat[i][i] = inf before running the alg, after running the alg if AdjMat[i][i] is no
// longer inf then there is a circle, if it is negative then there is a negative circle in graph
// to find cheapest circle check all adjMat[i][i] for the minimum one.


// 2.transitive closure.
// to see if there is any path from i to j transitive closure alg is used.
for (int k = 0; k < V; k++)
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			AdjMat[i][j] |= (AdjMat[i][k] & AdjMat[k][j]);


// 3.Minmax
// just replace + operator with max operator --> max(AdjMat[i][k], AdjMat[k][j])


// 4. check if i and j belong to the same SCC, after finding transitive closure, if AdjMat[i][j] && AdjMat[j][i]
// is true then i and j belong to the same SCC.

// 5. find number of paths from i to j, just modify floyd warshals so instead of
// AdjMat[i][j] = AdjMat[i][k] + AdjMat[k][j] we have AdjMat[i][j] = AdjMat[i][k] * AdjMat[k][j].
// after running floyds if AdjMat[k][k] is greater that 0 then for each i and j such that 
// AdjMat[i][k] > 0 && AdjMat[k][j] is true there are infinit number of paths between i and j
// because there is a cirlce for k then you can allways go back to k and reach j again.
// in main AdjMat is 0 for all i and j except for ones that has an edge.
